// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STUDIO_H
#define _DYNAMIK_STUDIO_H

#include "GUI/ImGuiWrapper.h"

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
	};
}

#endif // !_DYNAMIK_STUDIO_H
