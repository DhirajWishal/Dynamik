#pragma once
#ifndef _DYNAMIK_COMPONENT_MANAGER_H
#define _DYNAMIK_COMPONENT_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "Macros/Global.h"
#include "Components/MeshComponent.h"
#include "ComponentArray.h"

namespace Dynamik
{
	/*
	 Component manager for the Dynamik Engine
	 This manager is set per component and holds all the supported components. Some of the main components
	 are:
	 * Mesh Component
	 * Audio Component
	 * Physics Body
	*/
	class DMK_API DMKComponentManager {
	public:
		DMKComponentManager() {}
		~DMKComponentManager();

		template<class COMPONENT>
		void registerComponent()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (componentTypes.find(componentName).size())
			{
				DMK_ERROR_BOX("Registering component already exists!");
			}

			components[componentName] = (POINTER<IComponentArray>)StaticAllocator<DMKComponentArray<COMPONENT>>::allocate();
			componentTypes.pushBack(componentName);
		}

		template<class COMPONENT>
		void addComponent(const COMPONENT& component)
		{
			getComponentArray<COMPONENT>()->myComponents.pushBack(component);
		}

		template<class COMPONENT>
		POINTER<DMKComponentArray<COMPONENT>> getComponentArray()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (!componentTypes.find(componentName).size())
			{
				DMKErrorManager::issueWarnBox(DMK_TEXT("Requested component does not exist! Creating a new component."));
				registerComponent<COMPONENT>();
			}

			return (POINTER<DMKComponentArray<COMPONENT>>)components[componentName];
		}

		template<class COMPONENT>
		POINTER<COMPONENT> getComponent(UI64 index = 0)
		{
			return getComponentArray<COMPONENT>()->myComponents.location(index);
		}

	private:
		std::unordered_map<STRING, POINTER<IComponentArray>> components;
		ARRAY<STRING> componentTypes;
	};
}

#endif // !_DYNAMIK_COMPONENT_MANAGER_H
