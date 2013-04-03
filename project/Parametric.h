#pragma once

#include <map>



namespace omoba
{


	typedef std::map<int,float>				Attributes;
	typedef Attributes::iterator			AttributeItr;
	typedef std::pair<int,float>			Attribute;

	

	enum SpriteAttribute
	{
	
		SPRITE_ATTRIBUTE_MOVEMENT_SPEED,
		SPRITE_ATTRIBUTE_ATACK_SPEED,
		SPRITE_ATTRIBUTE_COOLDOWN_REDUCTION,
		SPRITE_ATTRIBUTE_ARMOR_PENETRATION
	}
	
	
	
	class AttributeHolder
	{

		public:
		
			bool		getAttributeExists ( const int attributeId );
		
			float		getAttributeValue ( const int attributeId );

			void		setAttributeValue ( const int attributeId , const float attributeValue );
			
			void		removeAttribute ( const int attributeId );	
			
			class		ExcUndefinedAttribute { };
			
		private:
		
			void 		checkAttributeExists ( const int attributeId );

			Attributes	attributes;

	};

};