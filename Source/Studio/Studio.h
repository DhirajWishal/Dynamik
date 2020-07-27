// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STUDIO_H
#define _DYNAMIK_STUDIO_H

#include "GUI/ImGuiWrapper.h"
#include "Window/WindowHandle.h"
#include "Events/EventPool.h"

namespace Dynamik
{
	/*
	 Main Dynamik Studio class
	*/
	class DMKStudio {
	public:
		/*
		 Default constructor.
		*/
		DMKStudio();

		/*
		 Default destructor.
		*/
		~DMKStudio();

		/*
		 Initialize the studio.
		*/
		void initialize();

		/*
		 Execute the studio.
		*/
		void execute();

		/*
		 Terminate the studio.
		*/
		void terminate();

	private:
		DMKImGuiWrapper imGuiWrapper;
		DMKEventPool myEventPool;
		DMKWindowHandle* pActiveWindow = nullptr;

	private:
		void initializeRuntimeSystems();

		DMKWindowHandle* createWindowHandle(I32 width, I32 height, STRING title);
	};
}

#endif // !_DYNAMIK_STUDIO_H
