// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_ARRAY_H
#define _DYNAMIK_COMPONENT_ARRAY_H

#include "Core/Components/Component.h"
#include "Core/Types/TSArray.h"

namespace Dynamik
{
	/*
	 Component Array for the Game Entity Component system
	*/
	class DMK_API I_ComponentArray {
	public:
		I_ComponentArray() = default;
		virtual ~I_ComponentArray() = default;
	};

	/*
	 Component array for the Dynamik Engine
	*/
	template<class COMPONENT>
	class DMK_API DMKComponentArray : public I_ComponentArray {
	public:
		DMKComponentArray() = default;
		~DMKComponentArray() = default;

		TSArray<COMPONENT> myComponents;
	};
}

#endif // !_DYNAMIK_COMPONENT_ARRAY_H
