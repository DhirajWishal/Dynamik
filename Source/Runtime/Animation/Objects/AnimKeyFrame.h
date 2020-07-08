// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_KEY_FRAME_H
#define _DYNAMIK_ANIMATION_KEY_FRAME_H

#include "AnimNodeTransform.h"
#include <unordered_map>

namespace Dynamik
{
	/*
	 Dynamik Animation Key Frame
	*/
	class DMK_API DMKAnimKeyFrame {
	public:
		DMKAnimKeyFrame() {}
		DMKAnimKeyFrame(const F32& timeStamp, const std::unordered_map<STRING, DMKAnimNodeTransform>& transform)
			: timeStamp(timeStamp), transform(transform) {}
		~DMKAnimKeyFrame() {}

		/*
		 Get the time stamp of the current frame.
		*/
		F32 getTimeStamp() const;

		/*
		 Get a node transform from the node name.
		*/
		DMKAnimNodeTransform getNodeTransform(const STRING& name) const;

		/*
		 Get the whole transform map of the current key frame.
		*/
		std::unordered_map<STRING, DMKAnimNodeTransform> getTransformMap() const;

		/* Current Node Transform */
		mutable std::unordered_map<STRING, DMKAnimNodeTransform> transform;

		/* Current Key Frame Time Stamp */
		F32 timeStamp = 0.0f;
	};
}

#endif // !_DYNAMIK_ANIMATION_KEY_FRAME_H
