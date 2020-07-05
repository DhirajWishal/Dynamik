// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LISTENER_SERVICES_H
#define _DYNAMIK_LISTENER_SERVICES_H

#include "Core/Macros/Global.h"

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
	};
}

#endif // !_DYNAMIK_LISTENER_SERVICES_H
