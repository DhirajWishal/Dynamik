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
	
	void DMKCameraModule::updateMatrix()
	{
		matrix.view = DMKMathFunctions::lookAt(position, position + front, cameraUp);
		matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(fieldOfView), aspectRatio, nearRender, farRender);
	}
}
