#include "SpriteDataParser.h"

#include "../../o__O/String/String.h"

using namespace omoba;



//	ExcSpriteDataParsingError

												ExcSpriteDataParsingError::ExcSpriteDataParsingError ( const SpriteDataComponent spriteDataComponent )
													:
														spriteDataComponent(spriteDataComponent)
{

}



//	ASpriteDataProvider

												ASpriteDataProvider::ASpriteDataProvider ( void )
{

}

												ASpriteDataProvider::ASpriteDataProvider ( const std::string& spriteData )
													:
														spriteData(spriteData)
{
	
}

void											ASpriteDataProvider::setSpriteData ( const std::string& spriteData )
{

	this->spriteData = spriteData;

}

void											ASpriteDataProvider::parseSpriteData ( void )
{

}



//	SpriteDataParserXml

												SpriteDataParserXml::SpriteDataParserXml ( void )
{

}

												SpriteDataParserXml::SpriteDataParserXml ( const std::string& spriteData )
													:
														ASpriteDataProvider(spriteData)
{

}

void											SpriteDataParserXml::parseSpriteData ( void )
{

	//	Deleting previously parsed data
	this->clearParsedData();

	// Creating XML document of the raw sprite data
	this->spriteDataXml.Parse
	(
		this->spriteData.data(),
		0,
		TIXML_ENCODING_UTF8
	);
	
	//	Parsing XML sprite data
	this->parseSpriteMeshFile();
	
	this->parseSpriteViewDirection();
	
	this->parseSpriteParameters();

}

std::string										SpriteDataParserXml::getSpriteMeshFile ( void ) const
{

	return this->spriteMeshFile;
	
}

Ogre::Vector3									SpriteDataParserXml::getSpriteViewDirection ( void ) const
{

	return this->spriteViewDirection;

}

SpriteParameter									SpriteDataParserXml::getSpriteParameter ( const SpriteParameterId spriteParameterId ) const
{

	//	Looking for a requested parameter
	std::map<SpriteParameterId,SpriteParameter>::iterator spriteParameterItr;
	spriteParameterItr = this->spriteParameters.find(spriteParameterId);
	
	//	Requested parameter is not defined
	if ( spriteParameterItr == this->spriteParameters )
		throw ExcSpriteParameterUndefined { spriteParameterId };

	return spriteParameterItr->second;

}

void											SpriteDataParserXml::clearParsedData ( void )
{

	//	Truncating previously parsed data
	
	this->spriteMeshFile.clear();
	
	this->spriteViewDirection = Ogre::Vector3::ZERO;
	
	this->spriteParameters.clear();

}

void											SpriteDataParserXml::parseSpriteMeshFile ( void )
{

	TiXmlElement* meshFileXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("MESH_FILE");

	//	Requested XML element not found in the document
	if ( ! meshFileXmlElement )
		throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_MESH_FILE };
		
	//	Retrieve sprite mesh file from the node
	std::string spriteMeshFile = meshFileXmlElement->GetText();
	
	//	Sprite mesh file is not specified
	if ( spriteMeshFile.empty() )
		throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_MESH_FILE };
	
	//	Sprite mesh file successfully found
	this->spriteMeshFile = spriteMeshFile;

}

void											SpriteDataParserXml::parseSpriteViewDirection ( void )
{

	TiXmlElement* viewDirectionXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("VIEW_DIRECTION");

	//	Requested XML element not found in the document
	if ( ! viewDirectionXmlElement )
		throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_VIEW_DIRECTION };

	//	String representation of the view-direction vector
	std::string viewDirectionString = viewDirectionXmlElement->GetText();
	
	//	View direction vector is not specified
	if ( viewDirectionString.empty() )
		throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_VIEW_DIRECTION };
	
	//	Trying to convert a string representation of the vector to an Ogre representation
	try
	{

		//	';' character used as a delimiter of the vector components
		this->spriteViewDirection = OgreExtensions::Vector3(viewDirectionString,';');
	
	}
	
	//	String from the data file could not be converted to a vector
	catch ( OgreExtensions::Vector3::ExcStringToVectorConvertionError exception )
	{
	
		throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_VIEW_DIRECTION };
	
	}

}

void											SpriteDataParserXml::parseSpriteParameters ( void )
{

	//	Create empty map of parameters
	std::map<SpriteParameterId,SpriteParameter> spriteParameters;

	//	Retrieving parameters xml node
	TiXmlNode* parametersXmlNode = this->spriteDataXml.RootElement()->FirstChild("PARAMETERS");

	//	No PARAMETERS node found in the XML document
	if ( ! parametersXmlNode )
		throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_PARAMETERS };
	
	//	Iterating through all parameter elements
	TiXmlNode* parametersXmlNodeChild = NULL;
	while ( parametersXmlNodeChild = parametersXmlNode->IterateChildren(parametersXmlNodeChild) )
	{

		//	Gett parameter data
		o__O::String parameterIdString = parametersXmlNodeChild->Attribute("ID");
		o__O::String parameterValueInitialString = parametersXmlNodeChild->Attribute("VALUE_INITIAL");
		o__O::String parameterValueGrowthString = parametersXmlNodeChild->Attribute("VALUE_GROWTH");
		
		//	Check if parameter is defined correctly
		if
		(
			parameterIdString.getStdString().empty()
				||
			parameterValueInitialString.getStdString().empty()
				||
			parameterValueGrowthString.getStdString().empty()
		)
		{
		
			throw ExcSpriteDataParsingFailed { SPRITE_DATA_COMPONENT_PARAMETERS };
		
		}

		//	Converting parameter data to appropriate data types
		SpriteParameterId parameterId = static_cast<SpriteParameterId>(parameterIdString.toInt());
		float parameterValueInitial = parameterValueInitialString.toFloat();
		float parameterValueGrowth = parameterValueGrowthString.toFloat();
		SpriteParameter parameter { parameterValueInitial , parameterValueGrowth };

		//	Saving parameter data
		spriteParameters.insert(std::pair<SpriteParameterId,SpriteParameter>(parameterId,parameter);

	}
	
	this->spriteParameters = spriteParameters;

}