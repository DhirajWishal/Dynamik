#pragma once
#ifndef _DYNAMIK_MANAGER_OBJECT_H
#define _DYNAMIK_MANAGER_OBJECT_H

/*
 All the managers in the engine are derived from this.
 Core manager objects include:
 * Memory Manager
 * Error Manager
 * Asset Manager
 * Window Manager

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "../Component.h"

namespace Dynamik
{
	class DMK_API DMKManagerObject : public DMKComponent {
	public:
		DMKManagerObject() {}
		virtual ~DMKManagerObject() {}
	};
}

#endif // !_DYNAMIK_MANAGER_OBJECT_H
