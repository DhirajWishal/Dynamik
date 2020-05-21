#pragma once
#ifndef _DYNAMIK_GAME_OBJECT_H
#define _DYNAMIK_GAME_OBJECT_H

/*
 Game Object for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Object/GameComponent.h"
#include "Systems/Attachment/AttachmentManager.h"
#include "Object/Descriptors/MaterialDescriptor.h"

namespace Dynamik
{
	/* Dynamik Game Object Type */
	enum class DMK_API DMKGameObjectType {
		DMK_GAME_OBJECT_TYPE_DEBUG,         /* Debugging object */
		DMK_GAME_OBJECT_TYPE_MESH,          /* Bare mesh object */
		DMK_GAME_OBJECT_TYPE_STATIC,        /* Static object */
		DMK_GAME_OBJECT_TYPE_ANIMATED,      /* Animated object */
		DMK_GAME_OBJECT_TYPE_SKYBOX,        /* Skybox object */
		DMK_GAME_OBJECT_TYPE_CAMERA,        /* Camera object */
		DMK_GAME_OBJECT_TYPE_AUDIO,         /* Audio object */
		DMK_GAME_OBJECT_TYPE_VIDEO,         /* Video input */
		DMK_GAME_OBJECT_TYPE_TEXTURE_2D,    /* Texture object 2D */
		DMK_GAME_OBJECT_TYPE_TEXTURE_3D,    /* Texture object 3D */
		DMK_GAME_OBJECT_TYPE_LIGHTING,      /* Lighting object */

		DMK_GAME_OBJECT_TYPE_ENTITY_PLAYER, /* Lighting object */
		DMK_GAME_OBJECT_TYPE_ENTITY_NPC,    /* Lighting object */
	};

	/*
	 This is the main Game Object class for the Dynamik Engine.
	 All the user defined objects (Camera, Skybox, static object, audio component,...) are derived from this.
	 This object acts as a node in the Scene Component.
	 Resource data can be given for each object in two ways,
	 * Internally (By using DMKMeshComponent::createMesh() function)
	 * Externally (By linking a file containg model data)

	 Shader data can be passed to the engine by using a string containing all the data.
	 Textures are required to be passed by an external file.
	*/
	class DMK_API DMKGameObject : public DMKGameComponent {
	public:
		DMKGameObject() {}
		DMKGameObject(DMKGameObjectType ty) : DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_OBJECT), type(ty) {}
		virtual ~DMKGameObject() {}

		/* Initialize the object */
		virtual void initialize() {}

		DMKGameObjectType type = DMKGameObjectType::DMK_GAME_OBJECT_TYPE_STATIC;

		/* Material description of the game object */
		POINTER<DMKMaterialDescriptor> materialDescription;

		DMKAttachmentManager myAttachmentManager;
	};
}

#endif // !_DYNAMIK_GAME_OBJECT_H
