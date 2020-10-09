// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "CameraModule.h"

#include "Core/Math/MathFunctions.h"

DMKCameraModule::DMKCameraModule()
{
}

void DMKCameraModule::setViewPortExtent(DMKExtent2D extent)
{
	viewPortExtent = extent;
	aspectRatio = extent.width / extent.height;
}

void DMKCameraModule::update()
{
	matrix.view = DMKMathFunctions::lookAt(position, position + front, cameraUp);
	matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(fieldOfView), aspectRatio, nearRender, farRender);
}

void DMKCameraModule::updateVectors()
{
	VEC3 _front = VEC3(0.0f);
	_front.x = DMathLib::cos(DMKMathFunctions::radians(yaw)) * DMathLib::cos(DMKMathFunctions::radians(pitch));
	_front.y = DMathLib::sin(DMKMathFunctions::radians(pitch));
	_front.z = DMathLib::sin(DMKMathFunctions::radians(yaw)) * DMathLib::cos(DMKMathFunctions::radians(pitch));

	front = DMKMathFunctions::normalize(_front);
	right = DMKMathFunctions::normalize(DMKMathFunctions::cross(front, worldUp));
	cameraUp = DMKMathFunctions::normalize(DMKMathFunctions::cross(front, right));
}

void DMKCameraModule::updateMatrix()
{
	matrix.view = DMKMathFunctions::lookAt(position, position + front, cameraUp);
	matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(fieldOfView), aspectRatio, nearRender, farRender);
}

DMKCameraRay DMKCameraModule::generateRay(DMKExtent2D mousePosition)
{
	DMKCameraRay ray;
	ray.origin = position;

	auto rayEye = DMathLib::inverse(matrix.projection) *
		Vector4F(
			(2.0f * mousePosition.x) / viewPortExtent.width - 1.0f,
			(2.0f * mousePosition.y) / viewPortExtent.height - 1.0f,
			-1.0f, 1.0f);
	rayEye = Vector4F(rayEye.x, rayEye.y, -1.0f, 0.0f);

	auto rayWorld_v4 = (DMathLib::inverse(matrix.view) * rayEye);
	ray.direction = DMathLib::normalize(Vector3F(rayWorld_v4.x, rayWorld_v4.y, rayWorld_v4.z)) + position;

	return ray;
}

void DMKCameraModule::setParams(const DMKCameraViewParams& params)
{
	this->params = params;
}

DMKCameraViewParams DMKCameraModule::getViewParams() const
{
	return params;
}

void DMKCameraModule::setExposure(const F32& exposure)
{
	params.exposure = exposure;
}

void DMKCameraModule::setGamma(const F32& gamma)
{
	params.gamma = gamma;
}

F32 DMKCameraModule::getExposure() const
{
	return params.exposure;
}

F32 DMKCameraModule::getGamma() const
{
	return params.gamma;
}
