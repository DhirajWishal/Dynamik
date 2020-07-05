// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STUDIO_H
#define _DYNAMIK_STUDIO_H

#include "GUI/GUIManager/GUIManager.h"

namespace Dynamik
{
	/*
	 Dynamik Studio
	*/
	class DMKStudio {
	public:
		DMKStudio();
		~DMKStudio();

		void execute();

	private:
		void beginFrame();
		void updateFrame();
		void endFrame();

	private:
		GUIManager myGuiManager;
	};
}

#endif // !_DYNAMIK_STUDIO_H
