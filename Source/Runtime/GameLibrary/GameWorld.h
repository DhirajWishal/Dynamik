// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_WORLD_H
#define _DYNAMIK_GAME_WORLD_H

#include "Core/Types/ComplexTypes.h"
#include "Core/FileSystem/FileSystem.h"
#include "GameEntity.h"
#include "EnvironmentMap.h"

namespace Dynamik
{
	/* 
	 Dynamik Game World Light Component
	 This structure defines a global light component.
	*/
	struct DMK_API DMKGameWorldLightComponent {
		DMKColorComponent colorValue;
		Vector3F position = Vector3F(0.0f);
		Vector3F direction = Vector3F(0.0f);
	};

	/*
	 Dynamik Game World
	 This object represents a game world and may or may not contain behavior defined entities.  

	 The Game World is initialized on creation (by the constructor). Users are required to include
	 all the initialization and other functions in the constructor of your derived class.
	*/
	class DMK_API DMKGameWorld {
	public:
		DMKGameWorld() {}
		virtual ~DMKGameWorld() {}

		void initializeEntities();

		/*
		 Setup Camera Module
		 This function sets the camera module to all the stored entities.
		*/
		void setCamera(DMKCameraModule* pCameraModule);

	public:		/* Environment Map */
		/* Environment Map Pointer */
		DMKEnvironmentMap* pEnvironmentMap = nullptr;

		void setEnvironmentMap(DMKEnvironmentMap* pEnvironment);
		void loadEnvironmentMap(ARRAY<STRING> texturePaths);
		void loadEnvironmentMap(STRING texturePath);

	public:		/* Light Component */
		/* Global Light Components */
		ARRAY<DMKGameWorldLightComponent> globalLightComponents;

		void addLightComponent(DMKGameWorldLightComponent component);

	public:		/* Entity */
		/* Entity Array */
		ARRAY<DMKGameEntity*> entities;

		/*
		 Create a basic hollow entity.
		 These entities does not have any functionalities and are basically empty.
		 By default, this adds the entity to the entity array.
		*/
		DMKGameEntity* createHollowEntity();

		/*
		 Create static object entity.
		 This entity contains a static mesh without any other functionality attached to it by default.
		 By default, this adds the entity to the entity array.
		*/
		DMKGameEntity* createStaticEntity(const STRING& assetPath);

		/*
		 Create static entity.
		 This entity contains a static mesh without any other functionality attached to it by default.
		 By default, this adds the entity to the entity array.
		*/
		DMKGameEntity* createStaticEntity(const STRING& assetPath, const DMKVertexLayout& vertexLayout);

		/* TEMPLATED
		 Create user defined entity.
		 This creates a user defined entity, adds it to the entity list and returns its address.

		 @tparam ENTITY: The user defined entity
		*/
		template<class ENTITY>
		DMK_FORCEINLINE DMKGameEntity* createUserEntity()
		{
			DMKGameEntity* entity = Cast<DMKGameEntity*>(StaticAllocator<ENTITY>::allocate().get());

			entities.pushBack(entity);
			return entity;
		}

		/*
		 Add an entity to the entity array.

		 @param pEntity: Pointer to the entity.
		*/
		void addEntity(DMKGameEntity* pEntity);

		/*
		 Create an empty environment.
		*/
		DMKEnvironmentMap* createHollowEnvironment();
	};
}

#endif // !_DYNAMIK_GAME_WORLD_H
