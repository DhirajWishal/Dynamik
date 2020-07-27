// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IM_GUI_BACKEND_HANDLE_H
#define _DYNAMIK_IM_GUI_BACKEND_HANDLE_H

#include "Core/Macros/Global.h"
#include <imgui.h>

namespace Dynamik
{
	/*
	 Dynamik Im Gui Backend Handle
	 This object is the base class for all the Im Gui backend implementations and is user accessible.
	*/
	class DMK_API DMKImGuiBackendHandle {
	public:
		DMKImGuiBackendHandle() {}
		virtual ~DMKImGuiBackendHandle() {}

		virtual void initialize() = 0;
		virtual void update(ImDrawData* pDrawData) = 0;
		virtual void drawFrame() = 0;
		virtual void terminate() = 0;
	};
}

#endif // !_DYNAMIK_IM_GUI_BACKEND_HANDLE_H
