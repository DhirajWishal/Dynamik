// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_PLAYER_H
#define _DYNAMIK_ANIMATION_PLAYER_H

#include "GameLibrary/Entities/AnimatedModelEntity.h"
#include "Core/Utilities/Ticker.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Player
	 This object plays a provided animation.
	*/
	class DMKAnimationPlayer {
	public:
		DMKAnimationPlayer() {}
		~DMKAnimationPlayer() {}

		/*
		 Begin playing the animation.
		*/
		void beginPlay(DMKAnimatedModelEntity* pAnimatedMesh, UI64 animationIndex);

		/*
		 Update the animation.
		*/
		void updatePlay();

		/*
		 End playing the animation.
		*/
		void endPlay();

	public:	
		DMKTicker myTicker;
		DMKAnimatedModelEntity* pCurrentAnimation = nullptr;
		DMKAnimation* pAnimation = nullptr;
		UI64 animationIndex = 0;
	};
}

#endif // !_DYNAMIK_ANIMATION_PLAYER_H
