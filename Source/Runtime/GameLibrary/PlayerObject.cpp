// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PlayerObject.h"
#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKPlayerObject::updateCamera()
	{
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
	
	void DMKPlayerObject::setCameraPosition(const VEC3& position)
	{
		cameraModule.position = position;
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