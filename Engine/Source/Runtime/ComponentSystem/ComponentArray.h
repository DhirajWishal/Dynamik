#pragma once
#ifndef _DYNAMIK_COMPONENT_ARRAY_H
#define _DYNAMIK_COMPONENT_ARRAY_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "Component.h"
#include "Types/TSArray.h"

namespace Dynamik
{
	/*
	 Component array for the Dynamik Engine
	*/
	template<class COMPONENT>
	class DMK_API DMKComponentArray : public DMKComponent {
	public:
		DMKComponentArray() {}
		~DMKComponentArray() {}

		TSArray<COMPONENT> myComponents;
	};
}

#endif // !_DYNAMIK_COMPONENT_ARRAY_H
