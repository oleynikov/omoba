#include "SpriteDataParser.h"

#include "../../o__O/String/String.h"

using namespace omoba;



//	ExcSpriteDataParsingError

												ExcSpriteDataParsingError::ExcSpriteDataParsingError ( const SpriteDataComponent spriteDataComponent )
													:
														spriteDataComponent(spriteDataComponent)
{

}



//	ASpriteDataParser

												ASpriteDataParser::ASpriteDataParser ( void )
{

}

												ASpriteDataParser::ASpriteDataParser ( const std::string& spriteData )
													:
														spriteData(spriteData)
{
	
}

void											ASpriteDataParser::setSpriteData ( const std::string& spriteData )
{

	this->spriteData = spriteData;

}

void											ASpriteDataParser::parseSpriteData ( void )
{

}



//	SpriteDataParserXml

												SpriteDataParserXml::SpriteDataParserXml ( void )
{

}

												SpriteDataParserXml::SpriteDataParserXml ( const std::string& spriteData )
													:
														ASpriteDataParser(spriteData)
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

float											SpriteDataParserXml::getSpriteParameterValueInitial ( const SpriteParameterId spriteParameterId ) const
{

	//	Looking for a parameter
	std::map<SpriteParameterId,float[2]>::iterator spriteParameterItr;
	spriteParameterItr = this->spriteParameters.find(spriteParameterId);
	
	if ( spriteParameterItr == this->spriteParameters )
		throw ExcSpriteParameterNotFound();

	return spriteParameterItr.second[0];
	
}
			
float											SpriteDataParserXml::getSpriteParameterValueGrowth ( const SpriteParameterId spriteParameterId ) const
{

	//	Looking for a parameter
	std::map<SpriteParameterId,float[2]>::iterator spriteParameterItr;
	spriteParameterItr = this->spriteParameters.find(spriteParameterId);
	
	if ( spriteParameterItr == this->spriteParameters )
		throw ExcSpriteParameterNotFound();

	return spriteParameterItr.second[1];

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
	std::map<SpriteParameterId,float[2]> spriteParameters;

	//	Retrieving parameters xml node
	TiXmlNode* parametersXmlNode = this->spriteDataXml.RootElement()->FirstChild("PARAMETERS");

	//	Error occured while parsing
	if ( ! parametersXmlNode )
		throw ExcParsingError();
	
	//	Iterating through all parameter elements
	TiXmlNode* parametersXmlNodeChild = NULL;
	while ( parametersXmlNodeChild = parametersXmlNode->IterateChildren(parametersXmlNodeChild) )
	{

		//	Getting parameter data
		o__O::String parameterIdString = parametersXmlNodeChild->Attribute("ID");
		o__O::String parameterValueInitialString = parametersXmlNodeChild->Attribute("VALUE_INITIAL");
		o__O::String parameterValueGrowthPerLevelString = parametersXmlNodeChild->Attribute("VALUE_GROWTH_PER_LEVEL");

		//	Converting parameter data to appropriate format
		SpriteParameterId parameterId = static_cast<SpriteParameterId>(parameterIdString.toInt());
		float parameterValueInitial = parameterValueInitialString.toFloat();
		float parameterValueGrowthPerLevel = parameterValueGrowthPerLevelString.toFloat();
		float parameterData[2] = { parameterValueInitial , parameterValueGrowthPerLevel };

		//	Saving parameter data
		spriteParameters.insert(std::pair<SpriteParameterId,float[2]>(parameterId,parameterData);

	}
	
	this->spriteParameters = spriteParameters;

}