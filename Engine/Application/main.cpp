/*
 Application project of the Dynamik Engine.
 This project contains a basic example on how to code and use the Dynamik Engine on the client size.
 This file contains the main entrypoint.

 Author:    Dhiraj Wishal
 Date:      14/05/2020 
*/

#include <iostream>
#include <vector>
#include "Core/Types/Array.h"
#include "Core/Error/ErrorManager.h"

int main() {
	std::cout << "Welcome to the Dynamik Engine v1\n";

    Dynamik::DMKErrorManager::issueWarnBox("Hello check?!");

	return 0;
}