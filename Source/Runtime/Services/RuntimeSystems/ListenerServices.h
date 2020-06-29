// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LISTENER_SERVICES_H
#define _DYNAMIK_LISTENER_SERVICES_H

/*
 Author:	Dhiraj Wishal
 Date:		29/06/2020
*/
#include "Core/Macros/Global.h"
#include "Events/Event/EventListener.h"

namespace Dynamik
{
	/*
	 Dynamik Listener Services
	 This provides listener services such as registering/ subscribing, unregistering/ unsubscribing from
	 services.

	 This object is best treated as a singleton.
	*/
	class DMK_API DMKListenerServices {
	public:
		DMKListenerServices() {}
		~DMKListenerServices() {}

		void addEventListener(DMKEventListener* pListener);
	};
}

#endif // !_DYNAMIK_LISTENER_SERVICES_H