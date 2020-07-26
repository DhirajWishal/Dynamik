// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IM_GUI_BACKEND_H
#define _DYNAMIK_IM_GUI_BACKEND_H

namespace Dynamik
{
	/*
	 Dynamik Im Gui Backend
	 This object stores all the backend information and functions needed to render Im Gui.
	*/
	class DMKImGuiBackend {
	public:
		DMKImGuiBackend() {}
		virtual ~DMKImGuiBackend() {}

		virtual void initialize() = 0;
		virtual void update() = 0;
		virtual void drawFrame() = 0;
		virtual void terminate() = 0;
	};
}

#endif // !_DYNAMIK_IM_GUI_BACKEND_H
