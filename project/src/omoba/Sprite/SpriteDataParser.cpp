#include "SpriteDataParser.h"

#include "../../o__O/String/String.h"

using namespace omoba;



//	ASpriteDataParser

												ASpriteDataParser::ASpriteDataParser ( void )
{

}

												ASpriteDataParser::ASpriteDataParser ( const std::string& spriteData )
{

	this->setSpriteData(spriteData);
	
}

void											ASpriteDataParser::setSpriteData ( const std::string& spriteData )
{

	this->spriteData = spriteData;
	this->parseSpriteData();

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

	//	Delete parsed data
	this->spriteMeshFile.clear();
	this->spriteViewDirection = Ogre::Vector3::ZERO;
	this->spriteParameters.clear();

	// Creating XML document of sprite data
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
			
float											SpriteDataParserXml::getSpriteParameterValueGrowthPerLevel ( const SpriteParameterId spriteParameterId ) const
{

	//	Looking for a parameter
	std::map<SpriteParameterId,float[2]>::iterator spriteParameterItr;
	spriteParameterItr = this->spriteParameters.find(spriteParameterId);
	
	if ( spriteParameterItr == this->spriteParameters )
		throw ExcSpriteParameterNotFound();

	return spriteParameterItr.second[1];

}

void											SpriteDataParserXml::parseSpriteMeshFile ( void )
{

	TiXmlElement* meshFileXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("MESH_FILE");

	//	Error occured while parsing
	if ( ! meshFileXmlElement )
		throw ExcSpriteDataParsingError();

	this->spriteMeshFile = meshFileXmlElement->GetText();

}

void											SpriteDataParserXml::parseSpriteViewDirection ( void )
{

	TiXmlElement* viewDirectionXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("VIEW_DIRECTION");

	//	Error occured while parsing
	if ( ! viewDirectionXmlElement )
		throw ExcSpriteDataParsingError();
	
	//	String representation of the view-direction vector
	char* viewDirectionString = viewDirectionXmlElement->GetText();
	
	//	Ogre representation of the view-direction vector
	//	';' character used as a delimiter of the vector components
	this->spriteViewDirection = OgreExtensions::Vector3(viewDirectionString,';');

}

void											SpriteDataParserXml::parseSpriteParameters ( void )
{

	//	Constructing parameters map
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