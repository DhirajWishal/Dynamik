#pragma once
#ifndef _DYNAMIK_COMPONENT_SUB_COMPONENT_MANAGER_H
#define _DYNAMIK_COMPONENT_SUB_COMPONENT_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		09/06/2020
*/
#include "SubComponentArray.h"

namespace Dynamik
{
	class DMK_API DMKSubComponentManager {
	public:
		DMKSubComponentManager() {}
		~DMKSubComponentManager();

		template<class COMPONENT>
		void registerSubComponent()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (subComponentTypes.find(componentName).size())
			{
				DMK_ERROR_BOX("Registering component already exists!");
			}

			subComponents[componentName] = (POINTER<ISubComponentArray>)StaticAllocator<DMKSubComponentArray<COMPONENT>>::allocate();
			subComponentTypes.pushBack(componentName);
		}

		template<class COMPONENT>
		void addSubComponent(const COMPONENT& component)
		{
			getComponentArray<COMPONENT>()->myComponents.pushBack(component);
		}

		template<class COMPONENT>
		POINTER<DMKSubComponentArray<COMPONENT>> getSubComponentArray()
		{
			STRING componentName = typeid(COMPONENT).name();

			if (!subComponentTypes.find(componentName).size())
			{
				DMKErrorManager::issueWarnBox(DMK_TEXT("Requested component does not exist! Creating a new component."));
				registerComponent<COMPONENT>();
			}

			return (POINTER<DMKSubComponentArray<COMPONENT>>)subComponents[componentName];
		}

		template<class COMPONENT>
		POINTER<COMPONENT> getSubComponent(UI64 index = 0)
		{
			return getComponentArray<COMPONENT>()->myComponents.location(index);
		}

	private:
		std::unordered_map<STRING, POINTER<ISubComponentArray>> subComponents;
		ARRAY<STRING> subComponentTypes;
	};
}

#endif // !_DYNAMIK_COMPONENT_SUB_COMPONENT_MANAGER_H
