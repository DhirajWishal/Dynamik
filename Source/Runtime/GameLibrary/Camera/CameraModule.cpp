// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "CameraModule.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	DMKCameraModule::DMKCameraModule()
	{
		myDescription = DMKUniformBufferObject::createUniformCamera();
	}
	
	void DMKCameraModule::update()
	{
		matrix.view = DMKMathFunctions::lookAt(position, position + front, cameraUp);
		matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(45.0f), 0.5f, 0.01f, 256.0f);
	}
	
	DMKUniformDescription DMKCameraModule::getDescription() const
	{
		return myDescription;
	}
	
	void DMKCameraModule::updateVectors()
	{
		VEC3 _front = VEC3(0.0f);
		_front.x = std::cos(DMKMathFunctions::radians(yaw)) * std::cos(DMKMathFunctions::radians(pitch));
		_front.y = std::sin(DMKMathFunctions::radians(pitch));
		_front.z = std::sin(DMKMathFunctions::radians(yaw)) * std::cos(DMKMathFunctions::radians(pitch));

		front = DMKMathFunctions::normalize(_front);
		right = DMKMathFunctions::normalize(DMKMathFunctions::cross(front, worldUp));
		cameraUp = DMKMathFunctions::normalize(DMKMathFunctions::cross(front, right));
	}

	void DMKCameraModule::updateMatrix()
	{
		matrix.view = DMKMathFunctions::lookAt(position, position + front, cameraUp);
		matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(fieldOfView), aspectRatio, nearRender, farRender);
	}
}
