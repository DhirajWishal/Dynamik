#include "dmkafx.h"
#include "CameraModule.h"

#include "Math/MathFunctions.h"

namespace Dynamik
{
	void DMKCameraModule::update(const DMKEventBuffer& eventBuffer)
	{
		viewMatrix = DMKMathFunctions::lookAt(position, position + front, cameraUp);
		projectionMatrix = DMKMathFunctions::perspective(DMKMathFunctions::radians(45.0f), 0.5f, 0.01f, 256.0f);
	}
}
