// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GameLibrary/GameComponents/GameModule.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace GameLibrary
	{
		void GameModule::LoadNextModule(GameModule* pNextModule)
		{
			// Check if the new module is valid.
			if (!pNextModule)
			{
				Logger::LogError(TEXT("Submitted module is invalid!"));
				return;
			}
		}

		void GameModule::UpdateEntities(float timeStep)
		{
			// Update all the entities.
			for (auto itr = updateList.begin(); itr != updateList.end(); itr++)
				for (auto pEntity = itr->second.begin(); pEntity != itr->second.end(); pEntity++)
					(*pEntity)->OnUpdate(timeStep);
		}

		void GameModule::DespawnAllEntities()
		{
			// Call the on Despawn method.
			for (auto itr = updateList.begin(); itr != updateList.end(); itr++)
				for (auto pEntity = itr->second.begin(); pEntity != itr->second.end(); pEntity++)
					(*pEntity)->OnDespawn();

			// Clear from the world state.
			ClearAllEntities();
		}

		void GameModule::AddEntityToUpdateList(GameEntity* pEntity, const char* pEntityName)
		{
			// Check if the entity and the entity name is valid.
			if (!pEntity || !pEntityName)
				return;

			// Add the entity to the update list.
			updateList[pEntityName].push_back(pEntity);
		}

		void GameModule::RemoveEntityFromUpdateList(const char* pEntityName, UI64 index)
		{
			// Check if the entity name is valid.
			if (!pEntityName)
				return;

			// Remove the entity if its registered.
			if (updateList.find(pEntityName) != updateList.end())
			{
				// Get the container and erase the entry.
				auto& vec = updateList[pEntityName];
				vec.erase(vec.begin() + index);
			}
		}
	}
}