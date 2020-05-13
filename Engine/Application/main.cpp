/*
 Application project of the Dynamik Engine.
 This project contains a basic example on how to code and use the Dynamik Engine on the client size.
 This file contains the main entrypoint.

 Author:    Dhiraj Wishal
 Date:      14/05/2020 
*/

#include <iostream>
#include "Core/Memory/MemoryPadding.h"

int main() {
	std::cout << "Welcome to the Dynamik Engine v1\n";
	DMKMemoryPadding<32> _padding;

	return 0;
}