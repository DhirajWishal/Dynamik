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

int main() {
	std::cout << "Welcome to the Dynamik Engine v1\n";

    Dynamik::ARRAY<Dynamik::UI32, 4U> _array;
    for (Dynamik::UI32 itr = 0; itr < 10000; itr++)
        _array.pushBack(itr);

    std::vector<Dynamik::UI32> _vector;
    for (Dynamik::UI32 itr = 0; itr < 10000; itr++)
        _vector.push_back(itr);

	return 0;
}