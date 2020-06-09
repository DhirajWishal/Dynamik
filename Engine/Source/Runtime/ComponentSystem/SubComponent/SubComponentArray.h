#pragma once
#ifndef _DYNAMIK_COMPONENT_SUB_COMPONENT_ARRAY_H
#define _DYNAMIK_COMPONENT_SUB_COMPONENT_ARRAY_H

/*
 Author:	Dhiraj Wishal
 Date:		09/06/2020
*/
#include "Core/Types/TSArray.h"

namespace Dynamik
{
	/*
	 Sub Component array base class
	*/
	class DMK_API ISubComponentArray {
	public:
		ISubComponentArray() {}
		virtual ~ISubComponentArray() {}
	};

	/*
	 Dynamik Sub Component Array
	*/
	template<class COMPONENT>
	class DMK_API DMKSubComponentArray : public ISubComponentArray {
	public:
		DMKSubComponentArray() {}
		~DMKSubComponentArray() {}

		TSArray<COMPONENT> myComponents;
	};
}

#endif // !_DYNAMIK_COMPONENT_SUB_COMPONENT_ARRAY_H
