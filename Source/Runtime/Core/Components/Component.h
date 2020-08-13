// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_H
#define _DYNAMIK_COMPONENT_H

#include "Core/Macros/Global.h"
#include "Core/Types/ObjectArray.h"

namespace Dynamik
{
	class DMK_API DMKSubComponent;

	/*
	 Dynamik Component Action 
	 This defines which action the component is currently going through.
	*/
	enum class DMK_API DMKComponentAction {
		DMK_COMPONENT_ACTION_INITIALIZE,
		DMK_COMPONENT_ACTION_SUBMIT_DATA,
		DMK_COMPONENT_ACTION_UPDATE,
		DMK_COMPONENT_ACTION_TERMINATE,
	};

	/*
	 Component object for the Dynamik Engine
	 This object is the base object for all the component in the Dynamik Engine. 
	*/
	class DMK_API DMKComponent {
	public:
		DMKComponent() {}
		virtual ~DMKComponent() {}

		virtual void initialize() {}
		virtual void submitData(STRING systemName) {}
		virtual void update(F32 timeFrame) {}
		virtual void terminate() {}
	};
}

#endif // !_DYNAMIK_COMPONENT_H
