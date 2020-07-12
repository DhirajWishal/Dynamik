// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GUI_CORE_H
#define _DYNAMIK_GUI_CORE_H

#include "Core/Macros/Global.h"

namespace Dynamik
{
	/*
	 GUI Core for the Dynamik Engine
	 This renderer uses OpenGL to render to a window which this class maintains. GUI elements are provided at
	 drawtime.
	*/
	class DMK_API GUICore {
	public:
		GUICore();
		GUICore(I32 width, I32 height, STRING title = "Dynamik Studio v1");
		~GUICore();

		void initialize();

		virtual void initializeFrame();
		virtual void updateRenderables();
		virtual void submitRenderables();

	protected:
		I32 windowWidth = 0;
		I32 windowHeight = 0;
		STRING windowTitle = TEXT("");

	private:
		static void _errorCallback(I32 ID, CCPTR description);
	};
}

#endif // !_DYNAMIK_GUI_CORE_H
