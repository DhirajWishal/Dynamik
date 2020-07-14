// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_H
#define _DYNAMIK_ANIMATION_H

#include "AnimKeyFrame.h"
#include "AnimNodePose.h"

namespace Dynamik
{
	/*
	 Dynamik Animation
	 This stores all the relevant information required to store and render animations.
	*/
	class DMK_API DMKAnimation {
	public:
		DMKAnimation() {}
		DMKAnimation(const F32& duration, const ARRAY<DMKAnimKeyFrame>& frames)
			: duration(duration), frames(frames) {}
		~DMKAnimation() {}

		/*
		 Get animation duration.
		*/
		F32 getDuration() const;

		/*
		 Get an animation frame using its index.
		*/
		DMKAnimKeyFrame getFame(I64 index = 0) const;

		/*
		 Get the whole frame store.
		*/
		ARRAY<DMKAnimKeyFrame> getFrames() const;

		/* Total Animation Duration */
		F32 duration = 0.0f;

		/* Animation Key Frames */
		ARRAY<DMKAnimKeyFrame> frames;
	};
}

#endif // !_DYNAMIK_ANIMATION_H
