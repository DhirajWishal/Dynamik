#include "dmkafx.h"
#include "CameraModule.h"

#include "Math/MathFunctions.h"

namespace Dynamik
{
	DMKCameraModule::DMKCameraModule()
	{
		myDescription = DMKUniformBufferObject::createUniformCamera();
	}
	
	void DMKCameraModule::update(const DMKEventBuffer& eventBuffer)
	{
		matrix.view = DMKMathFunctions::lookAt(position, position + front, cameraUp);
		matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(45.0f), 0.5f, 0.01f, 256.0f);
	}
	
	DMKUniformDescription DMKCameraModule::getDescription() const
	{
		return myDescription;
	}
}
