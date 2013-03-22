#pragma once

#include "InputDispatcher.h"

namespace omoba
{

	class InputListener
	{

		public:

			virtual void	keyPressHandler ( const KeyEvent& keyEvent );

			virtual void	keyReleaseHandler ( const KeyEvent& keyEvent );

			virtual void	mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void	mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void	mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

	};

};
