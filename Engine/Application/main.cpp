/*
 Application project of the Dynamik Engine.
 This project contains a basic example on how to code and use the Dynamik Engine on the client size.
 This file contains the main entrypoint.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/
#include "Dynamik.h"
using namespace Dynamik;

int main() 
{
	DMKEngineInstanceDescriptor _instanceDescriptor;
	DMKGamePackage _package;

	try
	{
		DMKEngine _engine(_instanceDescriptor, &_package);

		_engine.execute();
	}
	catch (const std::exception& e)
	{
		DMKErrorManager::logFatal(e.what(), __FILE__, __LINE__);
		return -1;
	}

	return 0;
}