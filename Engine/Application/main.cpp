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
#include "Math/Vector4D.h"
#include "Math/Matrix4F.h"

std::vector<float> add(std::vector<float> lhs, std::vector<float> rhs)
{
	std::vector<float> _container(4);
	for (int i = 0; i < lhs.size(); i++)
		_container[i] = (lhs[i] + rhs[i]);

	return _container;
}

int main() {
	Dynamik::DMKEngine::createInstance();

	Dynamik::Vector4F _v1 = { 0.0, 1.25, 2.0, 5.0 };
	Dynamik::Vector4F _v2 = { 0.0, 0, 0, 1 };
	Dynamik::Matrix4F _m1 = Dynamik::Matrix4F(1.0f);

	bool _v3 = !_v2;

	return 0;
}