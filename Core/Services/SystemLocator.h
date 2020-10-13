// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SYSTEM_LOCATOR_H
#define _DYNAMIK_SYSTEM_LOCATOR_H

#include "Core/Objects/System.h"
#include "Core/Types/ObjectArray.h"

/*
 Dynamik System Locator
 This is a service which allows users and internal components to directly interact with those systems.
*/
class DMK_API DMKSystemLocator {
	DMKSystemLocator() {}
	~DMKSystemLocator() {}

	static DMKSystemLocator instance;
public:
	/*
	 Create a new system and add it to the locator's list.
	 If the system is already available, a new system will not be added.

	 @param constructor: The constructor of the system. Default is SYSTEM().

	 @warn: This function is handled by the engine itself!
	*/
	template<class SYSTEM>
	static DMK_FORCEINLINE void createSystem(const SYSTEM& constructor = SYSTEM())
	{
		if (instance.systemArray.isRegistered<SYSTEM>())
		{
			DMK_ERROR("The requested system is already available!");
			return;
		}

		instance.systemArray.addObject<SYSTEM>(constructor);
	}

	/*
	 Check if a system is available.
	*/
	template<class SYSTEM>
	static DMK_FORCEINLINE bool isSystemAvailable()
	{
		return instance.systemArray.isRegistered<SYSTEM>();
	}

	/*
	 Get a system from the locator's list.
	*/
	template<class SYSTEM>
	static DMK_FORCEINLINE SYSTEM* getSystem()
	{
		return instance.systemArray.getObject<SYSTEM>(0);
	}

private:
	ObjectArray systemArray;
};

#endif // !_DYNAMIK_SYSTEM_LOCATOR_H
