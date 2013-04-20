#include "SpriteDataProvider.h"



using namespace omoba;


//	ASpriteDataProvider::ExcSpriteDataParsingFailed
												ASpriteDataProvider::ExcSpriteDataParsingFailed::ExcSpriteDataParsingFailed ( const SpriteDataComponent spriteDataComponent )
													:
														spriteDataComponent(spriteDataComponent)
{

}



//	ASpriteDataProvider::ExcSpriteParameterUndefined
												ASpriteDataProvider::ExcSpriteParameterUndefined::ExcSpriteParameterUndefined ( const SpriteParameterId spriteParameterId )
													:
														spriteParameterId(spriteParameterId)
{

}



//	SpriteDataProviderXml
												SpriteDataProviderXml::SpriteDataProviderXml ( ASpriteDataGetter& spriteDataGetter )
													:
														spriteDataGetter(spriteDataGetter)
{

		

}

std::string										SpriteDataProviderXml::getSpriteMeshFile ( const std::string& spriteName )
{
	
	this->updateSpriteData(spriteName);

	return this->spriteMeshFile;
	
}

Ogre::Vector3									SpriteDataProviderXml::getSpriteViewDirection ( const std::string& spriteName )
{

	this->updateSpriteData(spriteName);

	return this->spriteViewDirection;

}

SpriteParameter									SpriteDataProviderXml::getSpriteParameter ( const std::string& spriteName , const SpriteParameterId spriteParameterId )
{

	this->updateSpriteData(spriteName);

	//	Looking for a requested parameter
	std::map<SpriteParameterId,SpriteParameter>::const_iterator spriteParameterItr;
	spriteParameterItr = this->spriteParameters.find(spriteParameterId);
	
	//	Requested parameter is not defined
	if ( spriteParameterItr == this->spriteParameters.end() )
		throw ExcSpriteParameterUndefined ( spriteParameterId );

	return spriteParameterItr->second;

}

void											SpriteDataProviderXml::updateSpriteData ( const std::string& spriteName )
{

	if ( this->spriteName == spriteName )
		return;

	//	Deleting previously parsed data
	this->clearParsedData();

	//	Getting new sprite data
	std::string spriteData = this->spriteDataGetter.getSpriteData(spriteName);

	// Creating XML document of the raw sprite data
	this->spriteDataXml.Parse(spriteData.data(),0,TIXML_ENCODING_UTF8);

	//	Parsing data
	this->parseSpriteData();
	
}

void											SpriteDataProviderXml::parseSpriteData ( void )
{

	//	Parsing XML sprite data
	this->parseSpriteMeshFile();
	
	this->parseSpriteViewDirection();
	
	this->parseSpriteParameters();

}

void											SpriteDataProviderXml::clearParsedData ( void )
{

	//	Truncating previously parsed data
	
	this->spriteMeshFile.clear();
	
	this->spriteViewDirection = Ogre::Vector3::ZERO;
	
	this->spriteParameters.clear();

}

void											SpriteDataProviderXml::parseSpriteMeshFile ( void )
{

	TiXmlElement* meshFileXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("MESH_FILE");

	//	Requested XML element not found in the document
	if ( ! meshFileXmlElement )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_MESH_FILE );
		
	//	Retrieve sprite mesh file from the node
	std::string spriteMeshFile = meshFileXmlElement->GetText();
	
	//	Sprite mesh file is not specified
	if ( spriteMeshFile.empty() )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_MESH_FILE );
	
	//	Sprite mesh file successfully found
	this->spriteMeshFile = spriteMeshFile;

}

void											SpriteDataProviderXml::parseSpriteViewDirection ( void )
{

	TiXmlElement* viewDirectionXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("VIEW_DIRECTION");

	//	Requested XML element not found in the document
	if ( ! viewDirectionXmlElement )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_VIEW_DIRECTION );

	//	String representation of the view-direction vector
	std::string viewDirectionString = viewDirectionXmlElement->GetText();
	
	//	View direction vector is not specified
	if ( viewDirectionString.empty() )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_VIEW_DIRECTION );
	
	//	Trying to convert a string representation of the vector to an Ogre representation
	try
	{

		//	';' character used as a delimiter of the vector components
		this->spriteViewDirection = OgreExtensions::Vector3(viewDirectionString,';');
	
	}
	
	//	String from the data file could not be converted to a vector
	catch ( OgreExtensions::Vector3::ExcStringToVectorConvertionError exception )
	{
	
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_VIEW_DIRECTION );
	
	}

}

void											SpriteDataProviderXml::parseSpriteParameters ( void )
{

	//	Create empty map of parameters
	std::map<SpriteParameterId,SpriteParameter> spriteParameters;

	//	Retrieving parameters xml node
	TiXmlElement* parametersXmlNode = this->spriteDataXml.RootElement()->FirstChildElement("PARAMETERS");

	//	No PARAMETERS node found in the XML document
	if ( ! parametersXmlNode )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_PARAMETERS );
	
	//	Iterating through all parameter elements
	TiXmlNode* parametersXmlNodeChild = NULL;
	while ( parametersXmlNodeChild = parametersXmlNode->IterateChildren(parametersXmlNodeChild) )
	{

		//	Gett parameter data
		o__O::String parameterIdString = parametersXmlNodeChild->ToElement()->Attribute("ID");
		o__O::String parameterValueInitialString = parametersXmlNodeChild->ToElement()->Attribute("VALUE_INITIAL");
		o__O::String parameterValueGrowthString = parametersXmlNodeChild->ToElement()->Attribute("VALUE_GROWTH");
		
		//	Check if parameter is defined correctly
		if
		(
			parameterIdString.toStdString().empty()
				||
			parameterValueInitialString.toStdString().empty()
				||
			parameterValueGrowthString.toStdString().empty()
		)
		{
		
			throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_PARAMETERS );
		
		}

		//	Converting parameter data to appropriate data types
		SpriteParameterId parameterId = static_cast<SpriteParameterId>(parameterIdString.toInt());
		float parameterValueInitial = parameterValueInitialString.toFloat();
		float parameterValueGrowth = parameterValueGrowthString.toFloat();
		SpriteParameter parameter ( parameterValueInitial , parameterValueGrowth );

		//	Saving parameter data
		spriteParameters.insert(std::pair<SpriteParameterId,SpriteParameter>(parameterId,parameter));

	}
	
	this->spriteParameters = spriteParameters;

}