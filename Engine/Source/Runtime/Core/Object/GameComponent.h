#pragma once
#ifndef _DYNAMIK_GAME_COMPONENT_H
#define _DYNAMIK_GAME_COMPONENT_H

/*
 Dynamik Game Component for the Dynamik Engine.
 All the game library objects are derived from this.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Object.h"

namespace Dynamik
{
	class DMK_API DMKGameComponent : public DMKObject {
	public:
		DMKGameComponent() {}
		virtual ~DMKGameComponent() {}
	};
}

#endif // !_DYNAMIK_GAME_OBJECT_H
