#pragma once
#ifndef _DYNAMIK_PLAYER_ENTIRY_H
#define _DYNAMIK_PLAYER_ENTIRY_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "../GameEntity.h"

namespace Dynamik
{
	/*
	 Dynamik Player Entity
	 This entity defines the player in the game.
	*/
	class DMK_API DMKPlayerEntity : public DMKGameEntity {
	public:
		DMKPlayerEntity() {}
		virtual ~DMKPlayerEntity() {}
	};
}

#endif // !_DYNAMIK_PLAYER_ENTIRY_H
