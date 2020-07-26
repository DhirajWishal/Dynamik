// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Studio.h"

#include "Services/SystemLocator.h"
#include "Renderer/Renderer.h"

namespace Dynamik
{
	DMKStudio::DMKStudio()
	{
		DMK_INFO("Welcome to the Dynamik Studio!");
		imGuiWrapper.initialize();

		/* Initialize Runtime Systems */
		DMKSystemLocator::createSystem<DMKRenderer>();
		DMKSystemLocator::getSystem<DMKRenderer>()->initializeThread();
	}

	DMKStudio::~DMKStudio()
	{
		DMK_INFO("Shutting down the Dynamik Studio!");
		imGuiWrapper.terminate();
	}

	void DMKStudio::initialize()
	{
	}

	void DMKStudio::execute()
	{
		while (true)
		{

		}
	}

	void DMKStudio::terminate()
	{
	}
}
