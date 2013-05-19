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



//	ASpriteDataProvider::ExcSpriteParameterUndefined
												ASpriteDataProvider::ExcSpriteAnimationUndefined::ExcSpriteAnimationUndefined ( const SpriteAnimationId spriteAnimationId )
													:
														spriteAnimationId(spriteAnimationId)
{

}



//	SpriteDataProviderXml
												SpriteDataProviderXml::SpriteDataProviderXml ( o__O::ADataGetter& spriteDataGetter )
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

SpriteAnimation									SpriteDataProviderXml::getSpritAnimation ( const std::string& spriteName , const SpriteAnimationId spriteAnimationId )
{

	this->updateSpriteData(spriteName);

	//	Looking for a requested animation
	std::map<SpriteAnimationId,SpriteAnimation>::const_iterator spriteAnimationItr;
	spriteAnimationItr = this->spriteAnimations.find(spriteAnimationId);
	
	//	Requested animation is not defined
	if ( spriteAnimationItr == this->spriteAnimations.end() )
		throw ExcSpriteAnimationUndefined ( spriteAnimationId );

	return spriteAnimationItr->second;

}

void											SpriteDataProviderXml::updateSpriteData ( const std::string& spriteName )
{

	if ( this->spriteName == spriteName )
		return;

	//	Deleting previously parsed data
	this->clearParsedData();

	//	Getting new sprite data
	std::string spriteData = this->spriteDataGetter.getData(spriteName);

	// Creating XML document of the raw sprite data
	this->spriteDataXml.Parse(spriteData.data(),0,TIXML_ENCODING_UTF8);

	//	Parsing data
	this->parseSpriteData();

	//	Save sprite name
	this->spriteName = spriteName;
	
}

void											SpriteDataProviderXml::parseSpriteData ( void )
{

	//	Parsing XML sprite data
	this->parseSpriteMeshFile();
	
	this->parseSpriteViewDirection();
	
	this->parseSpriteParameters();

	this->parseSpriteAnimations();

}

void											SpriteDataProviderXml::clearParsedData ( void )
{

	//	Truncating previously parsed data
	this->spriteMeshFile.clear();
	this->spriteViewDirection = Ogre::Vector3::ZERO;
	this->spriteParameters.clear();

	//	Clear ths XML document
	this->spriteDataXml.Clear();

}

void											SpriteDataProviderXml::parseSpriteMeshFile ( void )
{

	TiXmlElement* meshFileXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("mesh_name");

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

	TiXmlElement* viewDirectionXmlElement = this->spriteDataXml.RootElement()->FirstChildElement("view_direction");

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
		this->spriteViewDirection = OgreAdaptor::Vector3(viewDirectionString,';');
	
	}
	
	//	String from the data file could not be converted to a vector
	catch ( OgreAdaptor::Vector3Exception::ExcStringToVectorConvertionError exception )
	{
	
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_VIEW_DIRECTION );
	
	}

}

void											SpriteDataProviderXml::parseSpriteParameters ( void )
{

	//	Create empty map of parameters
	std::map<SpriteParameterId,SpriteParameter> spriteParameters;

	//	Retrieving parameters xml node
	TiXmlElement* parametersXmlNode = this->spriteDataXml.RootElement()->FirstChildElement("parameters");

	//	No PARAMETERS node found in the XML document
	if ( ! parametersXmlNode )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_PARAMETERS );
	
	//	Iterating through all parameter elements
	TiXmlNode* parameterItemNode = NULL;
	while ( parameterItemNode = parametersXmlNode->IterateChildren(parameterItemNode) )
	{

		TiXmlElement* parameterItemElement = parameterItemNode->ToElement();

		if ( parameterItemElement == NULL )
			throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_PARAMETERS );

		//	Gett parameter data
		o__O::String parameterIdString = parameterItemElement->Attribute("id");
		o__O::String parameterValueInitialString = parameterItemElement->Attribute("value_initial");
		o__O::String parameterValueGrowthString = parameterItemElement->Attribute("value_growth");
		
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

void											SpriteDataProviderXml::parseSpriteAnimations ( void )
{

	//	Create empty map of animations
	std::map<SpriteAnimationId,SpriteAnimation> spriteAnimations;

	//	Retrieving animations xml node
	TiXmlElement* animationsXmlNode = this->spriteDataXml.RootElement()->FirstChildElement("animations");

	//	No `animations` node found in the XML document
	if ( ! animationsXmlNode )
		throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_ANIMATIONS );
	
	//	Iterating through all animations elements
	TiXmlNode* animationItemNode = NULL;
	while ( animationItemNode = animationsXmlNode->IterateChildren(animationItemNode) )
	{

		TiXmlElement* animationItemElement = animationItemNode->ToElement();

		if ( animationItemElement == NULL )
			throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_ANIMATIONS );

		//	Get animation data
		o__O::String animationIdString = animationItemElement->Attribute("id");
		o__O::String animationNameString = animationItemElement->Attribute("name");
		o__O::String parameterSpeedString = animationItemElement->Attribute("speed");
		
		//	Check if animation is defined correctly
		if
		(
			animationIdString.toStdString().empty()
				||
			animationNameString.toStdString().empty()
				||
			parameterSpeedString.toStdString().empty()
		)
		{
		
			throw ExcSpriteDataParsingFailed ( SPRITE_DATA_COMPONENT_ANIMATIONS );
		
		}

		//	Converting animation data to appropriate data types
		SpriteAnimationId animationId = static_cast<SpriteAnimationId>(animationIdString.toInt());
		std::string animationName = animationNameString.toStdString();
		float parameterSpeed = parameterSpeedString.toFloat();
		SpriteAnimation animation ( animationName , parameterSpeed );

		//	Saving animation data
		spriteAnimations.insert(std::pair<SpriteAnimationId,SpriteAnimation>(animationId,animation));

	}
	
	this->spriteAnimations = spriteAnimations;

}