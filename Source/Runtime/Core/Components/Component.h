// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_H
#define _DYNAMIK_COMPONENT_H

#include "Core/Macros/Global.h"
#include "Core/Types/TSArray.h"

namespace Dynamik
{
	/*
	 Component object for the Dynamik Engine
	*/
	class DMK_API DMKComponent {
	public:
		DMKComponent() {}
		virtual ~DMKComponent() {}
	};
}

#endif // !_DYNAMIK_COMPONENT_H
