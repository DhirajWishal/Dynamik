// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_ARRAY_H
#define _DYNAMIK_COMPONENT_ARRAY_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "Component.h"
#include "Types/TSArray.h"

namespace Dynamik
{
	/*
	 Component Array for the Game Entity Component system
	*/
	class DMK_API IComponentArray {
	public:
		IComponentArray() {}
		virtual ~IComponentArray() {}
	};

	/*
	 Component array for the Dynamik Engine
	*/
	template<class COMPONENT>
	class DMK_API DMKComponentArray : public IComponentArray {
	public:
		DMKComponentArray() {}
		~DMKComponentArray() {}

		TSArray<COMPONENT> myComponents;
	};
}

#endif // !_DYNAMIK_COMPONENT_ARRAY_H
