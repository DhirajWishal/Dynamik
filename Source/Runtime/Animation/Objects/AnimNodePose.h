// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_POSE_H
#define _DYNAMIK_ANIMATION_NODE_POSE_H

#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector/Vector3F.h"
#include "Core/Math/Matrix/Matrix4F.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node Pose
	 Defines a pose of a single node at a given time stamp.
	*/
	class DMK_API DMKAnimNodePose {
	public:
		DMKAnimNodePose() = default;
		DMKAnimNodePose(const UI64& index, const F32& duration, const Vector3F& position, const Vector3F& scale, const Quaternion& rotation)
			: nodeIndex(index), duration(duration), position(position), scale(scale), rotation(rotation) {}
		~DMKAnimNodePose() = default;

		/*
		 Interpolate this pose and the old pose.
		*/
		Matrix4F interpolate(DMKAnimNodePose oldPose, F32 frameTime);

		/*
		 Get the matrix using the rotation, position and scale.
		*/
		Matrix4F getMatrix();

		/* Rotation value */
		Quaternion rotation = Quaternion::Default;

		/* Position value */
		Vector3F position = Vector3F::ZeroAll;

		/* Scale value */
		Vector3F scale = Vector3F::ZeroAll;

		/* Node index */
		UI64 nodeIndex = 0;

		/* Pose duration */
		F32 duration = 0.0f;
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_POSE_H
