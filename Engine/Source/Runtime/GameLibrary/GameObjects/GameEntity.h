#pragma once
#ifndef _DYNAMIK_GAME_ENTITY_H
#define _DYNAMIK_GAME_ENTITY_H

/*
 Game Entiry for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "../GameObject.h"

namespace Dynamik
{
	/*
	 The entity class is the component which the user directly interact with. Player character and other
	 input based characters are derived from this.
	 Basically, Game Entities are of two types,
	 * Player character (The object which the user directly interacts with using the player controls)
	 * NPC (Non-Player Characters: The objects which the user/ player cannot directly interact/ control with)

	 Non Player Characters can either be hard coded or powered by the Interllect Engine. Intellect powered
	 entities can be trained either by scripting or by manual control.

	 By default, this class is initialized to be a Player entity.
	*/
	class DMK_API DMKGameEntity : public DMKGameObject {
	public:
		DMKGameEntity() : DMKGameObject(DMKGameObjectType::DMK_GAME_OBJECT_TYPE_ENTITY_PLAYER) {}
		virtual ~DMKGameEntity() {}
	};
}

#endif // !_DYNAMIK_GAME_ENTITY_H
