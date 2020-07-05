// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_MANAGER_H
#define _DYNAMIK_COMPONENT_MANAGER_H

#include "Core/Macros/Global.h"
#include "Core/Error/ErrorManager.h"
#include "Components/RenderableComponents/MeshComponent.h"
#include "ComponentArray.h"

namespace Dynamik
{
	/*
	 Component manager for the Dynamik Engine
	 This manager is set per component and holds all the supported components. Some of the main components
	 are:
	 * Mesh Component
	 * Audio Component
	*/
	class DMK_API DMKComponentManager {
	public:
		DMKComponentManager() {}
		~DMKComponentManager();

		/*
		 Register a component
		*/
		template<class COMPONENT>
		void registerComponent()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (componentTypes.find(componentName).size())
			{
				DMKErrorManager::issueErrorBox("Registering component already exists!");
			}

			components[componentName] = (I_ComponentArray*)StaticAllocator<DMKComponentArray<COMPONENT>>::allocate();
			componentTypes.pushBack(componentName);
		}

		/*
		 Create a new component and return its address.
		*/
		template<class COMPONENT>
		COMPONENT* createComponent()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (!componentTypes.find(componentName).size())
			{
				DMKErrorManager::logWarn(DMK_TEXT("Requested component does not exist! Creating a new component."));
				registerComponent<COMPONENT>();
			}

			addComponent(COMPONENT());

			return &getComponentArray<COMPONENT>()->myComponents[-1];
		}

		/*
		 Add a component
		*/
		template<class COMPONENT>
		void addComponent(const COMPONENT& component)
		{
			getComponentArray<COMPONENT>()->myComponents.pushBack(component);
		}

		/*
		 Get the component array
		*/
		template<class COMPONENT>
		DMKComponentArray<COMPONENT>* getComponentArray()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (!componentTypes.find(componentName).size())
			{
				DMKErrorManager::logWarn(DMK_TEXT("Requested component does not exist! Creating a new component."));
				registerComponent<COMPONENT>();
			}

			return (DMKComponentArray<COMPONENT>*)components[componentName];
		}

		/*
		 Get a component at a given index.
		 By default its 0.
		*/
		template<class COMPONENT>
		COMPONENT* getComponent(UI64 index = 0)
		{
			return (COMPONENT*)getComponentArray<COMPONENT>()->myComponents.location(index);
		}

	private:
		std::unordered_map<STRING, I_ComponentArray*> components;
		ARRAY<STRING> componentTypes;
	};
}

#endif // !_DYNAMIK_COMPONENT_MANAGER_H
