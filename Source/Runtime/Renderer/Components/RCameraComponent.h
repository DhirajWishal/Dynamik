// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_CAMERA_COMPONENT_H
#define _DYNAMIK_RENDERER_CAMERA_COMPONENT_H

#include "Primitives/RBuffer.h"
#include "GameLibrary/Camera/CameraModule.h"

namespace Dynamik
{
	/*
	 Renderer Camera Component
	*/
	class DMK_API RCameraComponent {
	public:
		RCameraComponent() = default;
		virtual ~RCameraComponent() = default;

		RBuffer* pUniformBuffer = nullptr;
		DMKCameraModule* pCameraModule = nullptr;
	};
}

#endif // !_DYNAMIK_RENDERER_CAMERA_COMPONENT_H
