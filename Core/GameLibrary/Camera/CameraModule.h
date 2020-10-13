// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CAMERA_MODULE_H
#define _DYNAMIK_CAMERA_MODULE_H

#include "Core/Macros/Global.h"
#include "Core/Math/MathTypes.h"
#include "Core/Objects/Resources/UniformBuffer.h"
#include "Core/Types/ComplexTypes.h"

/* Camera matrix */
struct DMK_API DMKCameraMatrix {
	MAT4 view = MAT4(1.0f);
	MAT4 projection = MAT4(1.0f);
};

/* A ray shot by the camera. Used for mouse picking. */
struct DMK_API DMKCameraRay {
	Vector3F origin;
	Vector3F direction;
};

/* Camera view params */
struct DMK_API DMKCameraViewParams {
	float exposure = 1.0f;
	float gamma = 1.0f;
};

/*
 Camera module for the Dynamik Engine.

 By default this object is bound to binding 1 in the vertex shader.
*/
class DMK_API DMKCameraModule {
public:
	DMKCameraModule();
	virtual ~DMKCameraModule() {}

	/*
	 Set the camera view port extent.

	 @param extent: Extent of the view port.
	*/
	void setViewPortExtent(DMKExtent2D extent);

	virtual void update();

	void updateVectors();
	virtual void updateMatrix();

	virtual DMKCameraRay generateRay(DMKExtent2D mousePosition);

	virtual void setParams(const DMKCameraViewParams& params);
	virtual DMKCameraViewParams getViewParams() const;
	virtual void setExposure(const float& exposure);
	virtual void setGamma(const float& gamma);
	virtual float getExposure() const;
	virtual float getGamma() const;

	DMKCameraMatrix matrix;

	VEC3 position = { 0.0f, 0.0f, 0.0f };
	VEC3 front = { 0.0f, 0.0f, -1.0f };
	VEC3 right = { 1.0f, 0.0f, 0.0f };
	VEC3 cameraUp = { 0.0f, 1.0f, 0.0f };
	VEC3 worldUp = { 0.0f, 1.0f, 0.0f };

	DMKExtent2D viewPortExtent;

	DMKCameraViewParams params = {};

	float fieldOfView = 45.0f;
	float farRender = 1024.0f;
	float nearRender = 0.001f;
	float aspectRatio = 1.77779f;

	float pitch = 0.0f;
	float roll = 0.0f;
	float yaw = 0.0f;
};

#endif // !_DYNAMIK_CAMERA_H