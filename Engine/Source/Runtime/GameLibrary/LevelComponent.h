#pragma once
#ifndef _DYNAMIK_LEVEL_COMPONENT_H
#define _DYNAMIK_LEVEL_COMPONENT_H

/*
 Dynamik Level Component.

 Author:	Dhiraj Wishal
 Date:		15/05/2020
*/

#include "Core/Object/GameComponent.h"
#include "SceneComponent.h"

namespace Dynamik
{
	/* Dynamik Level Component types */
	enum class DMK_API DMKLevelComponentType {
		DMK_LEVEL_COMPONENT_TYPE_INTERNAL,
		DMK_LEVEL_COMPONENT_TYPE_EXTERNAL,
	};

	/*
	 Dynamik Level Component act as a level for the Dynamik Engine.
	 All the scenes are loaded and presented as a level to the engine. Multiple levels can be loaded to the
	 memory at a given instance.
	 Levels are of two types:
	 * Internal (All of its data are defined in source files)
	 * External (All of its data are stored in external files (.fbx, .dae, etc...)

	 By default, this class can be used as an internal level component.
	*/
	class DMK_API DMKLevelComponent : public DMKGameComponent {
	public:
		DMKLevelComponent() : DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_LEVEL) {}
		DMKLevelComponent(DMKLevelComponentType ty) : type(ty) {}
		virtual ~DMKLevelComponent() {}

		DMKLevelComponentType type = DMKLevelComponentType::DMK_LEVEL_COMPONENT_TYPE_INTERNAL;

		/* Scene component store */
		ARRAY<POINTER<DMKSceneComponent>> mySceneComponents;
	};

	/*
	 Dynamik Engine supports importing levels stored in external files. The only requirement is that each
	 of the external levels should contain a level index file which indexes all the scene components the
	 level has. Once exported, the Resource manager will import the level and store all of its scene data
	 in the memory.
	 Users can either create scene components to all the scenes in the level index file which all the scene
	 data will be assigned to those components or new scene components will be created internally with game
	 objects initialized as static and assigned a new object to each mesh.
	 The Studio can index only one level at a time.
	*/
	class DMK_API DMKExternalLevelComponent : public DMKLevelComponent {
	public:
		DMKExternalLevelComponent() : DMKLevelComponent(DMKLevelComponentType::DMK_LEVEL_COMPONENT_TYPE_EXTERNAL) {}
		virtual ~DMKExternalLevelComponent() {}

		STRING levelIndexFilePath = "";
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
