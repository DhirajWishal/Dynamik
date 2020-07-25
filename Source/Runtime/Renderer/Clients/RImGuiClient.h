// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_IM_GUI_CLIENT_H
#define _DYNAMIK_RENDERER_IM_GUI_CLIENT_H

#include "../Components/RCoreObject.h"

namespace Dynamik
{
	/*
	 Renderer Im Gui client
	 This object is the main Im Gui backend for the Dynamik Engine.
	 Each RBL will contain an object which allows Im Gui to render its components through the active RBL.
	*/
	class DMK_API RImGuiClient {
	public:
		RImGuiClient() = default;
		virtual ~RImGuiClient() = default;

		virtual void initialize(RCoreObject* pCoreObject) = 0;
		virtual void update(RCoreObject* pCoreObject) = 0;
		virtual void drawFrame(RCoreObject* pCoreObject) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_IM_GUI_CLIENT_H
