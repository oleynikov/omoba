#pragma once

#include "ASceneNodeShifter.h"
#include "AInputListener.h"

namespace omoba
{

	class ASceneNodeShifterInteractive
		:
			public ASceneNodeShifter,
			public AInputListener
	{

		public:
			ASceneNodeShifterInteractive(void);
			~ASceneNodeShifterInteractive(void);

	};

};
