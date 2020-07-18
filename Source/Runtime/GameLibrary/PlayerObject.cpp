// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PlayerObject.h"
#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKPlayerObject::updateCamera()
	{
		cameraModule.updateVectors();
		cameraModule.updateMatrix();
	}
	
	void DMKPlayerObject::setPosition(const Vector3F& position)
	{
		this->position = position;
	}

	void DMKPlayerObject::addForwardVector(const F32& rate)
	{
		cameraModule.position += cameraModule.front * rate;
	}

	void DMKPlayerObject::addBackwardVector(const F32& rate)
	{
		cameraModule.position += (cameraModule.front * -1.0f) * rate;
	}

	void DMKPlayerObject::addLeftVector(const F32& rate)
	{
		cameraModule.position += (cameraModule.right * -1.0f) * rate;
	}

	void DMKPlayerObject::addRightVector(const F32& rate)
	{
		cameraModule.position += cameraModule.right * rate;
	}

	void DMKPlayerObject::addUpVector(const F32& rate)
	{
		cameraModule.position += cameraModule.cameraUp * rate;
	}

	void DMKPlayerObject::addDownVector(const F32& rate)
	{
		cameraModule.position += (cameraModule.cameraUp * -1.0f) * rate;
	}

	void DMKPlayerObject::addRotationX(F32 pitch)
	{
		cameraModule.pitch = pitch;
	}

	void DMKPlayerObject::addRotationY(F32 yaw)
	{
		cameraModule.yaw = yaw;
	}

	void DMKPlayerObject::addRotationZ(F32 roll)
	{
		cameraModule.roll = roll;
	}

	void DMKPlayerObject::processMouseControl(DMKExtent2D position, F32 sensitivity, B1 refresh, B1 flipAxises)
	{
		if (flipAxises)
		{
			position.x *= -1.0f;
			position.y *= -1.0f;
		}

		if (refresh || firstInput)
		{
			lastPosition = position;
			firstInput = false;
		}

		F32 xOffset = (position.x - lastPosition.x) * sensitivity;
		F32 yOffset = (lastPosition.y - position.y) * sensitivity;

		lastPosition = position;

		cameraModule.yaw += xOffset;
		cameraModule.pitch += yOffset;

		if (cameraModule.pitch > 89.0f)
			cameraModule.pitch = 89.0f;
		if (cameraModule.pitch < -89.0f)
			cameraModule.pitch = -89.0f;
	}

	void DMKPlayerObject::setCameraViewPort(DMKExtent2D extent)
	{
		cameraModule.setViewPortExtent(extent);
	}
	
	void DMKPlayerObject::setCameraPosition(const VEC3& position)
	{
		cameraModule.position = position;
	}

	void DMKPlayerObject::setCameraAndWorldUp(const VEC3& cameraUp, const VEC3& worldUp)
	{
		cameraModule.cameraUp = cameraUp;
		cameraModule.worldUp = worldUp;
	}

	void DMKPlayerObject::setCameraParams(F32 FOV, F32 aspect, F32 fNear, F32 fFar)
	{
		cameraModule.fieldOfView = FOV;
		cameraModule.aspectRatio = aspect;
		cameraModule.nearRender = fNear;
		cameraModule.farRender = fFar;
	}

	void DMKPlayerObject::setAspectRatio(F32 fAspect)
	{
		cameraModule.aspectRatio = fAspect;
	}

	void DMKPlayerObject::makeCameraRelative()
	{
		isCameraRelative = true;
	}

	void DMKPlayerObject::makeCameraStationary()
	{
		isCameraRelative = false;
	}

	DMKCameraModule* DMKPlayerObject::getCameraModule()
	{ 
		return &cameraModule;
	}
}