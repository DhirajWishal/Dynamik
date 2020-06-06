#pragma once
#ifndef _DYNAMIK_LEVEL_COMPONENT_H
#define _DYNAMIK_LEVEL_COMPONENT_H

/*
 Dynamik Level Component.

 Author:	Dhiraj Wishal
 Date:		15/05/2020
*/
#include "Core/Object/GameComponent.h"
#include "GameEntity.h"
#include "GameMechanics.h"
#include "Camera/CameraModule.h"

#include "Macros/Global.h"
#include "Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Level Component act as a level for the Dynamik Engine.
	 All the scenes are loaded and presented as a level to the engine. Multiple levels can be loaded to the
	 memory at a given 

	 By default, this class can be used as an internal level component.
	*/
	class DMK_API DMKLevelComponent : public DMKGameComponent {
	public:
		DMKLevelComponent() : DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_LEVEL) {}
		virtual ~DMKLevelComponent() {}

		virtual void onLoad() {}
		virtual void onUnoad() {}

		/* Game Assets */
		ARRAY<POINTER<DMKGameEntity>> myEntities;

		/* Game Mechanics */
		ARRAY<POINTER<DMKGameMechanics>> myMechanics;

		/* Camera component */
		POINTER<DMKCameraModule> cameraModule;

		/* Additional Components */
		DMKComponentManager globalComponentManager;
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
