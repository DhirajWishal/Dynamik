// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PRIMITIVE_COMPONENTS_H
#define _DYNAMIK_PRIMITIVE_COMPONENTS_H

#include "Core/Math/Matrix/Matrix4F.h"

namespace Dynamik
{
	/* Dynamik Transform Component */
	struct DMK_API DMKTransformComponent {
		DMKTransformComponent(const Matrix4F& mat) : matrix(mat) {}

		Matrix4F matrix = Matrix4F::Identity;
	};

	/* Dynamik Scale Component */
	struct DMK_API DMKScaleComponent {
		DMKScaleComponent(const Matrix4F& mat) : matrix(mat) {}

		Matrix4F matrix = Matrix4F::Identity;
	};

	/* Dynamik Rotation Component */
	struct DMK_API DMKRotationComponent {
		DMKRotationComponent(const Matrix4F& mat) : matrix(mat) {}

		Matrix4F matrix = Matrix4F::Identity;
	};
}

#endif // !_DYNAMIK_PRIMITIVE_COMPONENTS_H
