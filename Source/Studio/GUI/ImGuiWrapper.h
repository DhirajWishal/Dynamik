// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IM_GUI_WRAPPER_H
#define _DYNAMIK_IM_GUI_WRAPPER_H

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
		void terminate();
	};
}

#endif // !_DYNAMIK_IM_GUI_H
