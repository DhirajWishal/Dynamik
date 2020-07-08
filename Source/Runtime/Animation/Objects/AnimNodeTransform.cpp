// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNodeTransform.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	Matrix4F DMKAnimNodeTransform::getLocalTransform()
	{
		Matrix4F matrix = DMathLib::translate(Matrix4F(1.0f), position);
		return matrix * DMathLib::toRotationalMatrix(rotation);
	}
	
	void DMKAnimNodeTransform::interpolate(const DMKAnimNodeTransform& before, const DMKAnimNodeTransform& after, const F32& progression)
	{
		position = DMathLib::interpolate(before.position, after.position, progression);
		rotation = DMathLib::interpolate(before.rotation, after.rotation, progression);
	}
}
