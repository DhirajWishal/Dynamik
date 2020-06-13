#pragma once
#ifndef _DYNAMIK_LEVEL_COMPONENT_H
#define _DYNAMIK_LEVEL_COMPONENT_H

/*
 Dynamik Level Component.

 Author:	Dhiraj Wishal
 Date:		15/05/2020
*/
#include "GameEntity.h"
#include "GameMechanics.h"
#include "PlayerObject.h"

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
	class DMK_API DMKLevelComponent {
	public:
		DMKLevelComponent()  {}
		virtual ~DMKLevelComponent() {}

		virtual void onLoad() {}
		virtual void initializeComponents() {}
		virtual void onUnoad() {}

		/* Game Assets */
		ARRAY<POINTER<DMKGameEntity>> myEntities;

		/* Game Mechanics */
		ARRAY<POINTER<DMKGameMechanics>> myMechanics;

		/* Player Object */
		POINTER<DMKPlayerObject> playerObject;

		/* Additional Components */
		DMKComponentManager sceneComponentManager;

	public:		/* Constant methods */
		void initializeCameraModule();
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
