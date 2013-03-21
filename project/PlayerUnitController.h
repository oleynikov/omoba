#pragma once

#include <list>
#include "InputListener.h"



namespace omoba
{

    typedef std::list<PlayerUnit&>              PlayerUnits;
    
    typedef PlayerUnits::iterator               PlayerUnitItr;

    

	class PlayerUnitController
		:
            public InputListener
    
	{

		public:
            
                                                PlayerUnitController ( void );

                                                ~PlayerUnitController ( void );

                                                addUnit ( const PlayerUnit& playerUnit );

                                                removeUnit ( const PlayerUnit& playerUnit );

			virtual void                        mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void                        mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );

            virtual void                        mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );


            
		private:

            PlayerUnits                         playerUnits;

            static const OIS::MouseButtonID     mouseButtonSelectUnit;

			static const OIS::MouseButtonID     mouseButtonSetUnitTarget;

	};

};
