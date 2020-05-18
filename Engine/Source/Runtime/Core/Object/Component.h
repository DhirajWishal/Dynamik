#pragma once
#ifndef _DYNAMIK_COMPONENT_H
#define _DYNAMIK_COMPONENT_H

/*
 Dynamik Component super class for the Dynamik Engine.
 All the other Engine APIs, Managers and Servers are derived from this.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Object.h"

namespace Dynamik
{
	class DMK_API DMKComponent : public DMKObject {
	public:
		DMKComponent() {}
		virtual ~DMKComponent() {}
	};
}

#endif // !_DYNAMIK_COMPONENT_H
