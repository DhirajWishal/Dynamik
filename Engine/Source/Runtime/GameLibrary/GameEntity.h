#pragma once
#ifndef _DYNAMIK_GAME_ENTITY_H
#define _DYNAMIK_GAME_ENTITY_H

/*
 Game Entiry for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "Object/GameComponent.h"
#include "ComponentSystem/ComponentManager.h"

namespace Dynamik
{
	/*
	 The entity class is the component which the user directly interact with. Player character and other
	 input based characters are derived from this.
	 Basically, Game Entities are of two types,
	 * Player character (The object which the user directly interacts with using the player controls)
	 * NPC (Non-Player Characters: The objects which the user/ player cannot directly interact/ control with)

	 You can imagine entities as a soul. You are required to control it. 
	*/
	class DMK_API DMKGameEntity : public DMKGameComponent {
	public:
		DMKGameEntity() : DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_ENTITY) {}
		virtual ~DMKGameEntity() {}

		virtual void initialize() {}

		/* Component Manager */
		DMKComponentManager myComponentManager;
	};
}

#endif // !_DYNAMIK_GAME_ENTITY_H
