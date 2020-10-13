// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GlobalResourceStore.h"

namespace DMK
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Resource Container Object
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Resource Container Base object.
	 * This object is the base object for the resource containers.
	 */
	class ResourceContainerBase {
	public:
		/**
		 * Default constructor.
		 */
		ResourceContainerBase() {}

		/**
		 * Default destructor.
		 */
		virtual ~ResourceContainerBase() {}

		/**
		 * Get the number of elements stored in the container.
		 */
		virtual UI64 Size() const { return 0; }
	};

	/**
	 * Resource Container object.
	 * This object contains information about a perticular type using an Array.
	 *
	 * @tparam Type: The type of the data thats being stored.
	 * @tparam Array: The array type. Default is std::vector<Type>.
	 */
	template<class Type, class Array = std::vector<Type>>
	class ResourceContainer : public ResourceContainerBase {
	public:
		/**
		 * Default constructor.
		 */
		ResourceContainer() {}

		/**
		 * Default destructor.
		 */
		~ResourceContainer() {}

		/**
		 * Get the number of elements stored in the container.
		 */
		virtual UI64 Size() const override final { return dataStore.size(); }

		/**
		 * Add data to the end of the array.
		 *
		 * @param data: The data to be added.
		 */
		void PushBack(const Type& data)
		{
			dataStore.push_back(data);
		}

		/**
		 * Add data to the end of the array.
		 *
		 * @param data: The data to be added.
		 */
		void PushBack(Type&& data)
		{
			dataStore.push_back(std::move(data));
		}

		/**
		 * Get an element at a given index.
		 *
		 * @param index: The index to be accessed.
		 */
		Type& At(UI64 index)
		{
			return dataStore.at(index);
		}

		/**
		 * Get an element at a given index.
		 *
		 * @param index: The index to be accessed.
		 */
		const Type At(UI64 index) const
		{
			return dataStore.at(index);
		}

		/**
		 * Remove an element at a given index.
		 *
		 * @param index: The index of the element.
		 */
		void Remove(UI64 index)
		{
			dataStore.erase(dataStore.begin() + index);
		}

		/* Data */
	private:
		Array dataStore;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Resource Store Object
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Resource Store for the Global Resource Store.
	 */
	class ResourceStore {
	public:
		/**
		 * Default constructor.
		 */
		ResourceStore() {}

		/**
		 * Default destructor.
		 */
		~ResourceStore() {}

		/**
		 * Check if a resource is registerd.
		 *
		 * @tparam Type: The type to be checked.
		 */
		template<class Type>
		bool IsRegistered()
		{
			// Get the name of the type.
			STRING name = typeid(Type).name();

			// Iterate through the resource names to check if the name exists. 
			auto itr = resourceNames.begin();
			while (itr != resourceNames.end())
			{
				// Return true if the name is found. 
				if (*itr == name)
					return true;

				itr++;
			}

			// Return false.
			return false;
		}

		/**
		 * Register a resource in the resource store.
		 *
		 * @tparam Type: The resource type.
		 */
		template<class Type>
		void RegisterResource()
		{
			// Check if the resource is already registered.
			if (IsRegistered<Type>())
				return;

			// Get the name of the type.
			STRING name = typeid(Type).name();

			// Create a new container. 
			resourceMap[name] = new ResourceContainer<Type>();

			// Add the resource name to the array.
			resourceNames.push_back(name);
		}

		/**
		 * Get the resource container of a given type.
		 *
		 * @tparam Type: The type of the resource.
		 */
		template<class Type>
		ResourceContainer<Type>* GetResourceContainer()
		{
			// Register the resource type if not available. 
			RegisterResource<Type>();

			// Get the casted resource container. 
			return Inherit<ResourceContainer<Type>>(resourceMap[typeid(Type).name()]);
		}

		/**
		 * Add a resource to a resource container.
		 *
		 * @param resource: The resource to be added.
		 * @tparam Type: The type of the resource.
		 */
		template<class Type>
		void AddResource(const Type& resource)
		{
			GetResourceContainer<Type>()->PushBack(resource);
		}

		/**
		 * Get the number of elements stored in a given container.
		 *
		 * @tparam Type: The type of the container.
		 */
		template<class Type>
		UI64 Size()
		{
			return GetResourceContainer<Type>()->Size();
		}

	private:
		std::vector<STRING> resourceNames;
		std::unordered_map<STRING, ResourceContainerBase*> resourceMap;
	};

	// Global store instance.
	ResourceStore _GlobalStore;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//// Global Resource Store Definitions
	///////////////////////////////////////////////////////////////////////////////////////////////////

	namespace GlobalResourceStore
	{
		void SetResourceStore(const ResourceStore& store)
		{
			_GlobalStore = store;
		}

		ResourceStore& GetResourceStore()
		{
			return _GlobalStore;
		}
	}
}