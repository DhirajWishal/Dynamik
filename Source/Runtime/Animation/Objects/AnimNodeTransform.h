// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_TRANSFORM_H
#define _DYNAMIK_ANIMATION_NODE_TRANSFORM_H

#include "AnimNode.h"
#include "Core/Math/Vector/Vector3F.h"
#include "Core/Math/Quaternion.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node Transform
	*/
	class DMK_API DMKAnimNodeTransform {
	public:
		DMKAnimNodeTransform() {}
		DMKAnimNodeTransform(const Vector3F& position, const Quaternion& rotation) :
			position(position), rotation(rotation) {}
		~DMKAnimNodeTransform() {}

		/* Transform Position. Relative to the parent bone. */
		Vector3F position = Vector3F(0.0f);

		/* Transform Rotation */
		Quaternion rotation = Quaternion(0.0f);

		/*
		 Get the local transform of the node.
		*/
		Matrix4F getLocalTransform();

		/*
		 Interpolate node transform.
		*/
		void interpolate(const DMKAnimNodeTransform& before, const DMKAnimNodeTransform& after, const F32& progression);
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_TRANSFORM_H
