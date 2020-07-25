// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Studio.h"
using namespace Dynamik;

int main()
{
	try 
	{
		/* Instantiate the studio */
		DMKStudio studio;

		/* Initialize the studio */
		studio.initialize();

		/* Execute the studio */
		studio.execute();

		/* Terminate the studio */
		studio.terminate();
	}
	catch (std::exception& e)
	{
		DMKErrorManager::logError(e.what());

		return -1;
	}

	return 0;
}