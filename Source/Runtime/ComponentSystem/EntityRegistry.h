// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENTITY_REGISTRY_H
#define _DYNAMIK_ENTITY_REGISTRY_H

namespace Dynamik
{
	/*
	* Dynamik Entity Registry
	* This object stores all the entities (internally defined and user defined) at any given instance. This object is 
	* a singleton.
	*/
	class DMKEntityRegistry {
		DMKEntityRegistry() {}
		~DMKEntityRegistry() {}
	};
}

#endif // !_DYNAMIK_COMPONENT_REGISTRY_H
