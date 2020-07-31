// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IM_GUI_WRAPPER_H
#define _DYNAMIK_IM_GUI_WRAPPER_H

#include "Core/Types/ComplexTypes.h"
#include "Renderer/Clients/ImGuiBackendHandle.h"

namespace Dynamik
{
	/*
	 Dynamik Im Gui wrapper
	*/
	class DMKImGuiWrapper {
	public:
		DMKImGuiWrapper();
		~DMKImGuiWrapper();

		void initialize();
		void initializeBackend();
		void draw();
		void terminate();

		void update();

	private:
		DMKExtent2D windowExtent = { 1280.0f, 720.0f };
		DMKImGuiBackendHandle* myImGuiBackend = nullptr;
	};
}

#endif // !_DYNAMIK_IM_GUI_H
