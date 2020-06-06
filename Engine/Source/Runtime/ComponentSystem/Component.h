#pragma once
#ifndef _DYNAMIK_COMPONENT_H
#define _DYNAMIK_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "Macros/Global.h"
#include "Types/TSArray.h"

namespace Dynamik
{
	/*
	 Component object for the Dynamik Engine
	*/
	class DMK_API DMKComponent {
	public:
		DMKComponent() {}
		virtual ~DMKComponent() {}
	};
}

#endif // !_DYNAMIK_COMPONENT_H
