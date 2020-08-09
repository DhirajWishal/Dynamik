// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SUB_COMPONENT_H
#define _DYNAMIK_SUB_COMPONENT_H

#include "Core/Macros/Global.h"
#include "../Component.h"

namespace Dynamik
{
	/*
	* Dynamik Sub Component
	* This object is the base class for all the sub components in the component system.
	*/
	class DMK_API DMKSubComponent {
	public:
		DMKSubComponent() {}
		virtual ~DMKSubComponent() {}

		/*
		* Set the component which this sub component is attached to.
		* 
		* @param pComponent: The pointer to the component.
		*/
		virtual void setComponent(DMKComponent* pComponent) { this->pComponent = pComponent; }

		/* The parent component */
		DMKComponent* pComponent = nullptr;
	};
}

#endif // !_DYNAMIK_SUB_COMPONENT_H
