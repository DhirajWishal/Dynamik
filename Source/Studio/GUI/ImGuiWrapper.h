// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IM_GUI_WRAPPER_H
#define _DYNAMIK_IM_GUI_WRAPPER_H

#include "Core/Types/ComplexTypes.h"

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
		void terminate();

	private:
		DMKExtent2D windowExtent = { 1280.0f, 720.0f };
	};
}

#endif // !_DYNAMIK_IM_GUI_H
