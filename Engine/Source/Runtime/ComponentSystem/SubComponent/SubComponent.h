#pragma once
#ifndef _DYNAMIK_COMPONENT_SUB_COMPONENT_H
#define _DYNAMIK_COMPONENT_SUB_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		09/06/2020
*/
#include "Core/Macros/Global.h"
namespace Dynamik
{
	/*
	 Dynamik Sub Component
	 Sub Components define additional functions and resources of a component.
	*/
	class DMK_API DMKSubComponent {
	public:
		DMKSubComponent() {}
		virtual ~DMKSubComponent() {}
	};
}

#endif // !_DYNAMIK_COMPONENT_SUB_COMPONENT_H
