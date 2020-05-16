/*
 Application project of the Dynamik Engine.
 This project contains a basic example on how to code and use the Dynamik Engine on the client size.
 This file contains the main entrypoint.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include <iostream>
#include <vector>
#include "Dynamik.h"

#include "Math/Vector3D.h"

std::vector<float> add(std::vector<float> lhs, std::vector<float> rhs)
{
	std::vector<float> _container(4);
	for (int i = 0; i < lhs.size(); i++)
		_container[i] = (lhs[i] + rhs[i]);

	return _container;
}

int main() {
	Dynamik::DMKEngine::createInstance();

	for (int batch = 0; batch < 1000000; batch++)
	{
		std::vector<float> _test1 = { 0.0f, 1.0f, 2.0f, 3.0f };
		std::vector<float> _test2 = { 4.0f, 5.0f, 6.0f, 7.0f };
		auto _container1 = add(_test1, _test2);
	}

	for (int batch = 0; batch < 1000000; batch++)
	{
		Dynamik::Vector3D _test3 = { 0.0f, 1.0f, 2.0f, 3.0f };
		Dynamik::Vector3D _test4 = { 4.0f, 5.0f, 6.0f, 7.0f };
		auto _container2 = _test3 * _test4;
	}

	return 0;
}