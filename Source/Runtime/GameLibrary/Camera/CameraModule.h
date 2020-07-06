// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CAMERA_MODULE_H
#define _DYNAMIK_CAMERA_MODULE_H

#include "Core/Macros/Global.h"
#include "Core/Math/MathTypes.h"
#include "Core/Objects/Resource/Primitives.h"

namespace Dynamik
{
	/* Camera matrix */
	struct DMK_API DMKCameraMatrix {
		MAT4 view = MAT4(1.0f);
		MAT4 projection = MAT4(1.0f);
	};

	/*
	 Camera module for the Dynamik Engine.

	 By default this object is bound to binding 1 in the vertex shader.
	*/
	class DMK_API DMKCameraModule {
	public:
		DMKCameraModule();
		virtual ~DMKCameraModule() {}

		virtual void update();
		DMKUniformDescription getDescription() const;

		void updateVectors();
		virtual void updateMatrix();

		DMKCameraMatrix matrix;

		VEC3 position = { 0.0f, 0.0f, 0.0f };
		VEC3 front = { 0.0f, 0.0f, -1.0f };
		VEC3 right = { 1.0f, 0.0f, 0.0f };
		VEC3 cameraUp = { 0.0f, 1.0f, 0.0f };
		VEC3 worldUp = { 0.0f, 1.0f, 0.0f };

		F32 fieldOfView = 45.0f;
		F32 farRender = 256.0f;
		F32 nearRender = 0.001f;
		F32 aspectRatio = 0.5f;

		F32 pitch = 0.0f;
		F32 roll = 0.0f;
		F32 yaw = 0.0f;

	private:
		DMKUniformDescription myDescription;
	};
}

#endif // !_DYNAMIK_CAMERA_H
