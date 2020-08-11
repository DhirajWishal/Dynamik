// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_WORLD_H
#define _DYNAMIK_GAME_WORLD_H

#include "Core/Types/ComplexTypes.h"
#include "Core/Types/Utilities.h"
#include "Core/FileSystem/FileSystem.h"
#include "GameEntity.h"
#include "EnvironmentMap.h"

#include "Core/Components/Attachments/BoundingBox.h"

namespace Dynamik
{
	class DMK_API DMKGameModule;

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
	*/
	class DMK_API DMKGameWorld {
	public:
		DMKGameWorld() = default;
		virtual ~DMKGameWorld() = default;

		/*
		 Initialize the game world.
		 This function will be called upon creation of the object (Only if the provided functions are used).
		 IF the world is created and assigned by the user, this function needs to be explicitly called.
		*/
		virtual void initialize() {}

		/*
		 Initialize stored entities.
		*/
		void initializeEntities(DMKGameModule* pCurrentModule);

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

		template<class OBJECT>
		DMK_FORCEINLINE void createUserEnvironment(const OBJECT& environment)
		{
			pEnvironmentMap = StaticAllocator<OBJECT>::allocateInit(environment);
		}

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
		DMK_FORCEINLINE ENTITY* createUserEntity()
		{
			DMKGameEntity* entity = Cast<DMKGameEntity*>(StaticAllocator<ENTITY>::allocate().get());

			entities.pushBack(entity);
			return Cast<ENTITY*>(entity);
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

	/* WORLD LOG (#WorldID, #Date, #Time)

	 [Entity=Grass]
	 name="Grass01";
	 ID=0001;
	 instance {
		 location=(0.0f, 0.0f, 0.0f);			>> (x, y, z)
		 rotation=(0.0f, 0.0f, 0.0f, 0.0f);		>> (x, y, z, radians)
		 scale=(1.0f, 1.0f, 1.0f, 1.0f);		>> (x, y, z, scale)
	 };
	 instance {
		 location=(1.0f, 0.0f, 0.0f);			>> (x, y, z)
		 rotation=(0.0f, 0.0f, 0.0f, 0.0f);		>> (x, y, z, radians)
		 scale=(1.0f, 1.0f, 1.0f, 1.0f);		>> (x, y, z, scale)
	 };

	 GameWorld
	 {
	     auto m1 = addComponent<Model>(STRING);
		 auto a1 = addComponent<Audio>(STRING);
		 auto p1 = addComponent<PhysicsBox>(Size);

		 m1->addBehavior(StaticAllocator<Behavior1>::allocate());
		 m1->addInstance(Location, Rotation, Scale);
		 m1->addInstance(Location, Rotation, Scale);
		 m1->addInstance(Location, Rotation, Scale);

		 m1->addSubComponent(a1);
		 m1->addSubComponent(p1);

		 DMKComponentObject:
		   - onInitialize();
		   - onUpdate();
		   - onTerminate();
		   : StaticMesh
		   : AnimatedMesh
		   : Audio
	 }

	*/
}

#endif // !_DYNAMIK_GAME_WORLD_H
