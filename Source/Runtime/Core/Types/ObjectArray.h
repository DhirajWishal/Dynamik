// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_OBJECT_ARRAY_H
#define _DYNAMIK_OBJECT_ARRAY_H

/*
 Object arrays can store multiple arrays of different types. This is almost identical to arrays used by
 Entity Component Systems.
*/

#include "Array.h"
#include <unordered_map>

namespace Dynamik
{
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
	class DMK_API ObjectArrayType : public IObjectArrayBase, public ARRAY<OBJECT> {
	public:
		ObjectArrayType() : ARRAY<OBJECT>() {}
		ObjectArrayType(UI64 size) : ARRAY<OBJECT>(size) {}
		ObjectArrayType(UI64 size, const OBJECT& value) : ARRAY<OBJECT>(size, value) {}
		ObjectArrayType(const OBJECT* arr) : ARRAY<OBJECT>(arr) {}
		ObjectArrayType(std::initializer_list<OBJECT> list, UI64 size = 1) : ARRAY<OBJECT>(list, size) {}
		ObjectArrayType(const ARRAY<OBJECT>& arr) : ARRAY<OBJECT>(arr) {}
		ObjectArrayType(ARRAY<OBJECT>&& arr) : ARRAY<OBJECT>(std::move(arr)) {}
		ObjectArrayType(std::vector<OBJECT> vector) : ARRAY<OBJECT>(vector) {}
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

			if (registeredComponentTypes.find(objectName).size())
			{
				DMK_ERROR("Submitted Object Is Already Registered!");
				return;
			}

			objectArray[objectName] = StaticAllocator<ObjectArrayType<OBJECT>>::rawAllocate();
			registeredComponentTypes.pushBack(objectName);
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
			if (!registeredComponentTypes.find(objectName).size())
				registerObject<OBJECT>();

			return (ObjectArrayType<OBJECT>*)objectArray[objectName];
		}

		/*
		 Add an object to the array.
		*/
		template<class OBJECT>
		DMK_FORCEINLINE void addObject(const OBJECT& object)
		{
			getObjectArray<OBJECT>()->pushBack(object);
		}

		/*
		 Add multiple object of the same kind to the array.
		*/
		template<class OBJECT>
		DMK_FORCEINLINE void addObjects(ARRAY<OBJECT> objects)
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
			if (registeredComponentTypes.find(typeid(OBJECT).name()).size())
				return (OBJECT*)getObjectArray<OBJECT>()->location(index);

			return nullptr;
		}

		/*
		 Get all the requested objects stored in the class.
		 These data are copies of the original data and modifications will not get applies to the actual data.
		*/
		template<class OBJECT>
		DMK_FORCEINLINE ARRAY<OBJECT> getObjects()
		{
			if (!registeredComponentTypes.find(typeid(OBJECT).name()).size())
				return ARRAY<OBJECT>();

			ARRAY<OBJECT> objects;
			auto arr = getObjectArray<OBJECT>();

			for (auto elem : *arr)
				objects.pushBack(elem);

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
		ARRAY<STRING> getRegisteredComponentTypeNames()
		{
			return registeredComponentTypes;
		}

	private:
		std::unordered_map<STRING, IObjectArrayBase*> objectArray;
		ARRAY<STRING> registeredComponentTypes;
	};
}

#endif // !_DYNAMIK_OBJECT_ARRAY_H
