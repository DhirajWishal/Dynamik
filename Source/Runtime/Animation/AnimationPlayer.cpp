// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimationPlayer.h"

namespace Dynamik
{
	void DMKAnimationPlayer::beginPlay(DMKAnimatedModelEntity* pAnimatedMesh, UI64 animationIndex)
	{
		pCurrentAnimation = pAnimatedMesh;
		this->animationIndex = animationIndex;
		pAnimation = &pAnimatedMesh->animations[animationIndex];
		myTicker.start();
	}

	void DMKAnimationPlayer::updatePlay()
	{
	}

	void DMKAnimationPlayer::endPlay()
	{
		myTicker.end();
	}
}
