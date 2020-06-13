// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CAMERA_MODULE_H
#define _DYNAMIK_CAMERA_MODULE_H

/*
 Author:	Dhiraj Wishal
 Date:		03/06/2020
*/
#include "Macros/Global.h"
#include "Math/MathTypes.h"
#include "Events/EventHandler.h"
#include "Core/Object/Resource/Primitives.h"

namespace Dynamik
{
	/* Camera matrix */
	struct DMK_API DMKCameraMatrix {
		MAT4F view = MAT4F(1.0f);
		MAT4F projection = MAT4F(1.0f);
	};

	/*
	 Camera module for the Dynamik Engine.
	*/
	class DMK_API DMKCameraModule {
	public:
		DMKCameraModule();
		virtual ~DMKCameraModule() {}

		virtual void update(const DMKEventBuffer& eventBuffer);
		DMKUniformDescription getDescription() const;

		DMKCameraMatrix matrix;

		VEC3F position = { 0.0f, 0.0f, 0.0f };
		VEC3F front = { 0.0f, 0.0f, 1.0f };
		VEC3F right = { 1.0f, 0.0f, 0.0f };
		VEC3F cameraUp = { 0.0f, 1.0f, 0.0f };
		VEC3F worldUp = { 0.0f, 1.0f, 0.0f };

	private:
		DMKUniformDescription myDescription;
	};
}

#endif // !_DYNAMIK_CAMERA_H
