// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_TRANSFORM_H
#define _DYNAMIK_ANIMATION_NODE_TRANSFORM_H

#include "AnimNode.h"
#include "AnimTypes.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node Transform
	*/
	class DMK_API DMKAnimNodeTransform {
	public:
		DMKAnimNodeTransform() {}
		DMKAnimNodeTransform(AVectorFrame position, AQuatFrame rotation, AVectorFrame scale) :
			positionFrame(position), rotationFrame(rotation), scaleFrame(scale) {}
		~DMKAnimNodeTransform() {}

		/* Transform Rotation Frame */
		AQuatFrame rotationFrame;

		/* Transform Position Frame. Relative to the parent bone. */
		AVectorFrame positionFrame;

		/* Transform Scale Frame */
		AVectorFrame scaleFrame;

		/*
		 Interpolate node transform.
		*/
		static Matrix4F interpolate(const DMKAnimNodeTransform& before, const DMKAnimNodeTransform& after, const F32& frameTime);
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_TRANSFORM_H