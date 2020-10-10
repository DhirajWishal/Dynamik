// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_GLOBAL_RESOUCE_STORE_H
#define _DYNAMIK_CORE_GLOBAL_RESOUCE_STORE_H

#include "Core/Types/DataTypes.h"
#include "Core/Types/Utilities.h"
#include <mutex>

std::mutex _MutexGRS;

namespace DMK
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Resource Index Object
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Resource Index Object.
	 * This object is used to access or identify any resource in the global resource locator.
	 */
	template<class Type>
	class ResourceIndex {
	public:
		/**
		 * Default constructor.
		 *
		 * @param index: The index of the resource.
		 */
		ResourceIndex(UI64 index = 0) : index(index) {}

		/**
		 * Default destructor.
		 */
		~ResourceIndex() {}

		// Resource type of the index. 
		using ResourceType = Type;

		// The index of the relavent array. 
		UI64 index = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Global Resource Store Namespace
	///////////////////////////////////////////////////////////////////////////////////////////////////

	// Decleration for the resource store.
	class ResourceStore;

	/**
	 * Global Resource Store for the Dynamik Engine.
	 * This is a namespace containing functions used to store and retrieve. information about all the
	 * user-accessible objects and structures.
	 */
	namespace GlobalResourceStore
	{
		/**
		 * Set Resource Store function.
		 * This function sets the resource store used globally by this thread.
		 *
		 * @param store: The resource store to be set.
		 */
		void SetResourceStore(const ResourceStore& store);

		/**
		 * Get the resource store of the current thread.
		 */
		ResourceStore& GetResourceStore();

		/**
		 * Store resource to the resource store.
		 * This method stores data in the resource store and return its index.
		 *
		 * @param resource: The resource to be added.
		 * @tparam Type> The resource type.
		 */
		template<class Type>
		DMK_FORCEINLINE ResourceIndex<Type> StoreResource(const Type& resource)
		{
			// Lock this thread.
			std::lock_guard<std::mutex> _lock(_MutexGRS);

			// Add resource to the store.
			GetResourceStore().AddResource<Type>(resource);

			// Return the index.
			return ResourceIndex<Type>(GetResourceStore().Size<Type>() - 1);
		}

		/**
		 * Get a resource from the resource store.
		 *
		 * @param index: The resource index of the element to be accessed.
		 */
		template<class Type>
		DMK_FORCEINLINE Type& GetResource(const ResourceIndex<Type>& index)
		{
			return GetResourceStore().GetResourceContainer<Type>()->At(index.index);
		}

		/**
		 * Get a resource from the resource store.
		 *
		 * @param index: The resource index of the element to be accessed.
		 */
		template<class Type>
		DMK_FORCEINLINE Type GetResource(const ResourceIndex<Type>& index)
		{
			return GetResourceStore().GetResourceContainer<Type>()->At(index.index);
		}
	}
}

#endif // !_DYNAMIK_CORE_GLOBAL_RESOUCE_STORE_H
