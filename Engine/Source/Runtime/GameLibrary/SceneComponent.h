#pragma once
#ifndef _DYNAMIK_SCENE_COMPONENT_H
#define _DYNAMIK_SCENE_COMPONENT_H

/*
 Scene Component for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Object/GameComponent.h"
#include "Types/Pointer.h"

namespace Dynamik
{
	/* Dynamik Scene component types */
	enum class DMK_API DMKSceneComponentType {
		DMK_SCENE_COMPONENT_SINTERNAL,      /* Contents of the component are defined locally */
		DMK_SCENE_COMPONENT_EXTERNAL,      /* Contents of the component are defined externally */
	};

	/*
	 A Scene Component is used as a scene graph in the Dynamik Engine.
	 All the game objects are bound to their specific scene before submitting them to the engine. A scene
	 contains multiple game objects. A level component contains multiple scene components.
	 Each scene component are bound to a window/ portal. A window can be bound by multiple windows/ portals.
	 A scene can request to a new window/ portal which will be created on top of the parent window/ portal or else by
	 default every scene component is bound to the parent window/ portal.
	 Scene components are of two types:
	 * External (All the objects, including cameras, are defined externally (.fbx, .dae, etc...)
	 * Internal (All the objects and components are defined internally)
	 Users are required to derive their own scene from this (internal or external) class to create their own scne
	 components prior to submittion.
	*/
	class DMK_API DMKSceneComponent : public DMKGameComponent {
	public:
		DMKSceneComponent(DMKSceneComponentType ty) : DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_SCENE), type(ty) {}
		virtual ~DMKSceneComponent() {}

		STRING sceneName = DMK_TEXT("");
		DMKSceneComponentType type = DMKSceneComponentType::DMK_SCENE_COMPONENT_SINTERNAL;
		UI32 sceneID = 0;
	};

	/*
	 Internal scene components are defined in this class.
	*/
	class DMK_API DMKInternalSceneComponent : public DMKSceneComponent {
	public:
		DMKInternalSceneComponent() : DMKSceneComponent(DMKSceneComponentType::DMK_SCENE_COMPONENT_SINTERNAL) {}
		virtual ~DMKInternalSceneComponent() {}
	};

	/*
	 External scene components are defined in this class.
	 When prividing an external scene component to the engine, users are required to create a scene index file
	 which contains paths to all the asset index files which contains the asset data.
	 Users can either pre create game objects for all the importing files or else each mesh will be assigned to
	 a completely new game object created as static. The only exception to this is that the camera data will be
	 set to the default camera of the engine.
	*/
	class DMK_API DMKExternalSceneComponent : public DMKSceneComponent {
	public:
		DMKExternalSceneComponent() : DMKSceneComponent(DMKSceneComponentType::DMK_SCENE_COMPONENT_EXTERNAL) {}
		virtual ~DMKExternalSceneComponent() {}

		STRING sceneIndexFile = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_SCENE_COMPONENT_H
