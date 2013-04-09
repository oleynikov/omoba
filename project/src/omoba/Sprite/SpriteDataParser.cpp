#include "SpriteDataParser.h"

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

std::string										SpriteDataParserXml::getSpriteMeshFile ( void ) const
{

	TiXmlElement* meshFileXmlElement = this->spriteXmlData.RootElement()->FirstChildElement("MESH_FILE");

	//	Error occured while parsing
	if ( ! meshFileXmlElement )
		throw ExcParsingError();

	return std::string(meshFileXmlElement->GetText());
	
}

Ogre::Vector3									SpriteDataParserXml::getSpriteViewDirection ( void ) const
{

	TiXmlElement* viewDirectionXmlElement = this->spriteXmlData.RootElement()->FirstChildElement("VIEW_DIRECTION");

	//	Error occured while parsing
	if ( ! viewDirectionXmlElement )
		throw ExcParsingError();
	
	//	String representation of the view-direction vector
	char* viewDirectionString = viewDirectionXmlElement->GetText();
	
	//	Ogre representation of the view-direction vector
	//	';' character used as a delimiter of the vector components
	Ogre::Vector3 viewDirectionVector = OgreExtensions::Vector3(viewDirectionString,';');
	
	return viewDirectionVector;

}

IConfiguration<std::string,std::string>			SpriteDataParserXml::getSpriteAnimations ( void ) const
{

	//	Constructing a new configuration object
	IConfiguration<std::string,std::string> configurationOfAnimations;

	//	Retrieving animations xml node
	TiXmlNode* animationsXmlNode = this->spriteXmlData.RootElement()->FirstChild("ANIMATIONS");

	//	Error occured while parsing
	if ( ! animationsXmlNode )
		throw ExcParsingError();
	
	//	Iterating through all animation elements
	TiXmlNode* animationsXmlNodeChild = NULL;
	while ( animationsXmlNodeChild = animationsXmlNode->IterateChildren(animationsXmlNodeChild) )
	{

		//	Getting animation parameters
		char* animationId = animationsXmlNodeChild->Attribute("ID");
		char* animationName = animationsXmlNodeChild->Attribute("NAME");
		
		//	Adding an animation parameter to the configuration
		configurationOfAnimations.setParameter(animationId,animationName);
	
	}
	
	return configurationOfAnimations;

}

IConfiguration<std::string,float>				SpriteDataParserXml::getSpriteParameters ( void ) const
{

	//	Constructing a new configuration object
	IConfiguration<std::string,float> configurationOfParameters;

	//	Retrieving parameters xml node
	TiXmlNode* parametersXmlNode = this->spriteXmlData.RootElement()->FirstChild("PARAMETERS");

	//	Error occured while parsing
	if ( ! parametersXmlNode )
		throw ExcParsingError();
	
	//	Iterating through all parameter elements
	TiXmlNode* parametersXmlNodeChild = NULL;
	while ( parametersXmlNodeChild = parametersXmlNode->IterateChildren(parametersXmlNodeChild) )
	{

		//	Getting parameter data
		char* parameterIdString = parametersXmlNodeChild->Attribute("ID");
		char* parameterValueString = parametersXmlNodeChild->Attribute("VALUE_INITIAL");
		char* parameterValueGrowthPerLeverString = parametersXmlNodeChild->Attribute("VALUE_GROWTH_PER_LEVEL");
		
		//	Constructing a parameter object
		IParameter<float> parameterObject(atof(parameterValueString));
		
		//	Adding an animation parameter to the configuration
		configurationOfParameters.setParameter(parameterIdString,parameterObject);
	
	}
	
	return configurationOfParameters;

}

void											SpriteDataParserXml::parseSpriteData ( void )
{

	// Parsing sprite data using UTF-8 encoding
	this->spriteXmlData.Parse
	(
		this->spriteXmlData.data(),
		0,
		TIXML_ENCODING_UTF8
	);

}