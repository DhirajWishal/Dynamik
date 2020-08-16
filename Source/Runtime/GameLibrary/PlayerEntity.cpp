// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PlayerEntity.h"
#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKPlayerEntity::updateCamera()
	{
		cameraModule.updateVectors();
		cameraModule.updateMatrix();
	}
	
	void DMKPlayerEntity::setPosition(const Vector3F& position)
	{
		this->position = position;
	}

	void DMKPlayerEntity::addForwardVector(const F32& rate)
	{
		cameraModule.position += cameraModule.front * rate;
	}

	void DMKPlayerEntity::addBackwardVector(const F32& rate)
	{
		cameraModule.position += (cameraModule.front * -1.0f) * rate;
	}

	void DMKPlayerEntity::addLeftVector(const F32& rate)
	{
		cameraModule.position += (cameraModule.right * -1.0f) * rate;
	}

	void DMKPlayerEntity::addRightVector(const F32& rate)
	{
		cameraModule.position += cameraModule.right * rate;
	}

	void DMKPlayerEntity::addUpVector(const F32& rate)
	{
		cameraModule.position += cameraModule.cameraUp * rate;
	}

	void DMKPlayerEntity::addDownVector(const F32& rate)
	{
		cameraModule.position += (cameraModule.cameraUp * -1.0f) * rate;
	}

	void DMKPlayerEntity::addRotationX(F32 pitch)
	{
		cameraModule.pitch = pitch;
	}

	void DMKPlayerEntity::addRotationY(F32 yaw)
	{
		cameraModule.yaw = yaw;
	}

	void DMKPlayerEntity::addRotationZ(F32 roll)
	{
		cameraModule.roll = roll;
	}

	void DMKPlayerEntity::processMouseControl(DMKExtent2D position, F32 sensitivity, B1 refresh, B1 flipAxises)
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

	void DMKPlayerEntity::setCameraViewPort(DMKExtent2D extent)
	{
		cameraModule.setViewPortExtent(extent);
	}
	
	void DMKPlayerEntity::setCameraPosition(const VEC3& position)
	{
		cameraModule.position = position;
	}

	void DMKPlayerEntity::setCameraAndWorldUp(const VEC3& cameraUp, const VEC3& worldUp)
	{
		cameraModule.cameraUp = cameraUp;
		cameraModule.worldUp = worldUp;
	}

	void DMKPlayerEntity::setCameraParams(F32 FOV, F32 aspect, F32 fNear, F32 fFar)
	{
		cameraModule.fieldOfView = FOV;
		cameraModule.aspectRatio = aspect;
		cameraModule.nearRender = fNear;
		cameraModule.farRender = fFar;
	}

	void DMKPlayerEntity::setAspectRatio(F32 fAspect)
	{
		cameraModule.aspectRatio = fAspect;
	}

	void DMKPlayerEntity::makeCameraRelative()
	{
		isCameraRelative = true;
	}

	void DMKPlayerEntity::makeCameraStationary()
	{
		isCameraRelative = false;
	}

	DMKCameraModule* DMKPlayerEntity::getCameraModule()
	{ 
		return &cameraModule;
	}
}