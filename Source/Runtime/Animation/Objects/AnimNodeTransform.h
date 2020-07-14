// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_TRANSFORM_H
#define _DYNAMIK_ANIMATION_NODE_TRANSFORM_H

#include "AnimNodePose.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node Transform
	 This object contains all the poses a node will have when playing the animation.
	*/
	class DMK_API DMKAnimNodeTransform {
	public:
		DMKAnimNodeTransform() = default;
		~DMKAnimNodeTransform() = default;

		/*
		 Add a pose to the transform.
		*/
		void addPose(const DMKAnimNodePose& pose);

		/*
		 Get the interpolation between two node poses.
		*/
		Matrix4F getInterpolation(UI64 currentPose, UI64 nextPose, F32 frameTime);

		/*
		 Poses for a given node.
		*/
		ARRAY<DMKAnimNodePose> nodePoses;

		Matrix4F finalTransform = Matrix4F(1.0f);
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_TRANSFORM_H