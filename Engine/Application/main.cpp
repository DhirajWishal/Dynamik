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
	Dynamik::DMKEngine _engine;
	_engine.createInstance(Dynamik::DMKEngineInstanceDescriptor());
	_engine.createWindow();
	_engine.execute();

	return 0;
}