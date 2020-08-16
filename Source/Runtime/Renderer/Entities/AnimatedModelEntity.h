// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATED_MODEL_ENTITY_H
#define _DYNAMIK_ANIMATED_MODEL_ENTITY_H

#include "StaticModelEntity.h"
#include "Animation/Objects/Animation.h"

namespace Dynamik
{
	/*
	 Dynamik Animated Model Entity
	 This object holds information about an animated model.
	*/
	class DMK_API DMKAnimatedModelEntity : public DMKStaticModelEntity {
	public:
		DMKAnimatedModelEntity() {}
		virtual ~DMKAnimatedModelEntity() {}

		/*
		 Add an instance to the animated model.

		 @param name: The name of the instance.
		 @param position: The position of the instance.
		 @param rotation: The rotation of the instance.
		 @param scale: The scale of the instance.
		*/
		void addAnimationInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale) { addStaticInstance(name, position, rotation, scale); }
	
		/* Animations of the animated model */
		ARRAY<DMKAnimation> animations;
	};
}

#endif // !_DYNAMIK_ANIMATED_MODEL_ENTITY_H
