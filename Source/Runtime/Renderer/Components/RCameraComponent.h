// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_CAMERA_COMPONENT_H
#define _DYNAMIK_RENDERER_CAMERA_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		29/06/2020
*/
#include "Primitives/RBuffer.h"

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
	};
}

#endif // !_DYNAMIK_RENDERER_CAMERA_COMPONENT_H
