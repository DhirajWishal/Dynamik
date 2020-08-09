// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_BEHAVIOR_H
#define _DYNAMIK_BEHAVIOR_H

#include "SubComponent.h"

namespace Dynamik
{
	/*
	* Dynamik Behavior
	* This object defines a behavior of a component.
	*/
	class DMK_API DMKBehavior : public DMKSubComponent {
	public:
		DMKBehavior() {}
		virtual ~DMKBehavior() {}

		/*
		* This method defines what to do when the object is initialized. 
		* This function is automatically called by the components when added to it.
		*/
		virtual void onInitialize() {}

		/*
		* This function defines what to do when the component is updated.
		*/
		virtual void onUpdate() {}

		/*
		* This method defines what to do when the component is about to be terminated.
		* This is either explicitly or implicitly called by the engine upon termination of a component.
		*/
		virtual void onTerminate() {}
	};
}

#endif // !_DYNAMIK_BEHAVIOR_H
