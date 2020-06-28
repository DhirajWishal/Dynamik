// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

/*
 Application project of the Dynamik Engine.
 This project contains a basic example on how to code and use the Dynamik Engine on the client size.
 This file contains the main entry point.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/
#include "Dynamik.h"
#include "ApplicationPackage.h"
#include "Core/Math/MathFunctions.h"
using namespace Dynamik;

int main()
{
	DMKEngineInstanceDescriptor _instanceDescriptor;
	ApplicationPackage myPackage;

	try
	{
		/* Instantiate the engine */
		DMKEngine _engine(_instanceDescriptor, &myPackage);

		/* Execute the engine */
		_engine.execute();
	}
	catch (const std::exception& e)
	{
		DMKErrorManager::logFatal(e.what(), __FILE__, __LINE__);
		return -1;
	}

	return 0;
}