#pragma once
#ifndef _DYNAMIK_GAME_COMPONENT_H
#define _DYNAMIK_GAME_COMPONENT_H

/*
 Dynamik Game Component for the Dynamik Engine.
 All the game library objects are derived from this.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/
#include "Macros/Global.h"

namespace Dynamik
{
	enum class DMK_API DMKGameComponentType {
		DMK_GAME_COMPONENT_TYPE_LEVEL,
		DMK_GAME_COMPONENT_TYPE_SCENE,
		DMK_GAME_COMPONENT_TYPE_OBJECT,
		DMK_GAME_COMPONENT_TYPE_ENTITY,
		DMK_GAME_COMPONENT_TYPE_ATTACHMENT,
	};

	class DMK_API DMKGameComponent {
	public:
		DMKGameComponent() {}
		DMKGameComponent(DMKGameComponentType ty) : type(ty) {}
		virtual ~DMKGameComponent() {}

		DMKGameComponentType type = DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_OBJECT;
	};
}

#endif // !_DYNAMIK_GAME_OBJECT_H
