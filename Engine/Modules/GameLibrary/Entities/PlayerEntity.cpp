// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PlayerEntity.h"
#include "Core/Math/MathFunctions.h"

void DMKPlayerEntity::updateCamera()
{
	cameraModule.updateVectors();
	cameraModule.updateMatrix();
}

void DMKPlayerEntity::setPosition(const Vector3F& position)
{
	this->position = position;
}

void DMKPlayerEntity::addForwardVector(const float& rate)
{
	cameraModule.position += cameraModule.front * rate;
}

void DMKPlayerEntity::addBackwardVector(const float& rate)
{
	cameraModule.position += (cameraModule.front * -1.0f) * rate;
}

void DMKPlayerEntity::addLeftVector(const float& rate)
{
	cameraModule.position += (cameraModule.right * -1.0f) * rate;
}

void DMKPlayerEntity::addRightVector(const float& rate)
{
	cameraModule.position += cameraModule.right * rate;
}

void DMKPlayerEntity::addUpVector(const float& rate)
{
	cameraModule.position += cameraModule.cameraUp * rate;
}

void DMKPlayerEntity::addDownVector(const float& rate)
{
	cameraModule.position += (cameraModule.cameraUp * -1.0f) * rate;
}

void DMKPlayerEntity::addRotationX(float pitch)
{
	cameraModule.pitch = pitch;
}

void DMKPlayerEntity::addRotationY(float yaw)
{
	cameraModule.yaw = yaw;
}

void DMKPlayerEntity::addRotationZ(float roll)
{
	cameraModule.roll = roll;
}

void DMKPlayerEntity::processMouseControl(DMKExtent2D position, float sensitivity, bool refresh, bool flipAxises)
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

	float xOffset = (position.x - lastPosition.x) * sensitivity;
	float yOffset = (lastPosition.y - position.y) * sensitivity;

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

void DMKPlayerEntity::setCameraParams(float FOV, float aspect, float fNear, float fFar)
{
	cameraModule.fieldOfView = FOV;
	cameraModule.aspectRatio = aspect;
	cameraModule.nearRender = fNear;
	cameraModule.farRender = fFar;
}

void DMKPlayerEntity::setAspectRatio(float fAspect)
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
