// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_OBJECT_ARRAY_H
#define _DYNAMIK_OBJECT_ARRAY_H

/*
 Object arrays can store multiple arrays of different types. This is almost identical to arrays used by
 Entity Component Systems.
*/
#include "Core/Memory/StaticAllocator.h"

#include <vector>
#include <unordered_map>

/*
 Interface Object Array Base
*/
class DMK_API IObjectArrayBase {
public:
	IObjectArrayBase() = default;
	virtual ~IObjectArrayBase() = default;
};

/*
 Object Array Type for the Dynamik Engine
*/
template<class OBJECT>
class DMK_API ObjectArrayType : public IObjectArrayBase, public std::vector<OBJECT> {
public:
	ObjectArrayType() : std::vector<OBJECT>() {}
	ObjectArrayType(UI64 size) : std::vector<OBJECT>(size) {}
	ObjectArrayType(UI64 size, const OBJECT& value) : std::vector<OBJECT>(size, value) {}
	ObjectArrayType(const OBJECT* arr) : std::vector<OBJECT>(arr) {}
	ObjectArrayType(std::initializer_list<OBJECT> list, UI64 size = 1) : std::vector<OBJECT>(list, size) {}
	ObjectArrayType(const std::vector<OBJECT>& arr) : std::vector<OBJECT>(arr) {}
	ObjectArrayType(std::vector<OBJECT>&& arr) : std::vector<OBJECT>(std::move(arr)) {}
	ObjectArrayType(std::vector<OBJECT> vector) : std::vector<OBJECT>(vector) {}
	~ObjectArrayType() {}
};

/*
 Object Array for the Dynamik Engine.
*/
class DMK_API ObjectArray {
public:
	ObjectArray() {}
	~ObjectArray()
	{
		for (auto object : objectArray)
		{
			object.second->~IObjectArrayBase();
			StaticAllocator<IObjectArrayBase>::rawDeallocate(object.second, 0);

#ifdef DMK_DEBUG
			DMK_INFO("Deleting object array!");

#endif // DMK_DEBUG

		}
	}

	/*
	 Register a new object.
	 If already registered, issues an error to the log and returns.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE void registerObject()
	{
		STRING objectName = typeid(OBJECT).name();

		if (isRegistered<OBJECT>())
		{
			DMK_ERROR("Submitted Object Is Already Registered!");
			return;
		}

		objectArray[objectName] = StaticAllocator<ObjectArrayType<OBJECT>>::rawAllocate();
		registeredComponentTypes.push_back(objectName);
	}

	/*
	 Check if an object is already registered.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE bool isRegistered()
	{
		for (auto itr : registeredComponentTypes)
			if (itr == typeid(OBJECT).name())
				return true;

		return false;
	}

	/*
	 Return a given object array.
	 Returns nullptr if the array was not registered.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE ObjectArrayType<OBJECT>* getObjectArray()
	{
		STRING objectName = typeid(OBJECT).name();

		/* Check If Registered */
		if (!isRegistered<OBJECT>())
			registerObject<OBJECT>();

		return (ObjectArrayType<OBJECT>*)objectArray[objectName];
	}

	/*
	 Add an object to the array.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE void addObject(const OBJECT& object)
	{
		getObjectArray<OBJECT>()->push_back(object);
	}

	/*
	 Add multiple object of the same kind to the array.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE void addObjects(std::vector<OBJECT> objects)
	{
		for (auto object : objects)
			addObject<OBJECT>(object);
	}

	/*
	 Get an object stored in the array.
	 Returns nullptr if not registered.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE OBJECT* getObject(I64 index = 0)
	{
		if (isRegistered<OBJECT>())
			return (OBJECT*)&getObjectArray<OBJECT>()->at(index);

		return nullptr;
	}

	/*
	 Get all the requested objects stored in the class.
	 These data are copies of the original data and modifications will not get applies to the actual data.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE std::vector<OBJECT> getObjects()
	{
		if (!isRegistered<OBJECT>())
			return std::vector<OBJECT>();

		std::vector<OBJECT> objects;
		auto arr = getObjectArray<OBJECT>();

		for (auto elem : *arr)
			objects.push_back(elem);

		return objects;
	}

	/*
	 Return the last stored object in the array.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE OBJECT* getLast()
	{
		return getObject<OBJECT>(-1);
	}

	/*
	 Create a new object and return its address.
	*/
	template<class OBJECT>
	DMK_FORCEINLINE OBJECT* createObject()
	{
		addObject<OBJECT>(OBJECT());
		return getLast<OBJECT>();
	}

	/*
	 Get all the registered type names.
	*/
	std::vector<STRING> getRegisteredComponentTypeNames()
	{
		return registeredComponentTypes;
	}

private:
	std::unordered_map<STRING, IObjectArrayBase*> objectArray;
	std::vector<STRING> registeredComponentTypes;
};

#endif // !_DYNAMIK_OBJECT_ARRAY_H
