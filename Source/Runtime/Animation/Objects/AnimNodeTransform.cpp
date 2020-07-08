// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNodeTransform.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	Matrix4F DMKAnimNodeTransform::interpolate(const DMKAnimNodeTransform& before, const DMKAnimNodeTransform& after, const F32& frameTime)
	{
		Matrix4F matrix = Matrix4F(1.0f);

		/* Calculate Rotation Matrix */
		F32 delta = (frameTime - before.rotationFrame.duration) / (after.rotationFrame.duration - before.rotationFrame.duration);
		matrix = matrix * DMathLib::toRotationalMatrix(DMathLib::interpolate(before.rotationFrame.quat, after.rotationFrame.quat, delta));

		/* Calculate Translation Matrix */
		delta = (frameTime - before.positionFrame.duration) / (after.positionFrame.duration - before.positionFrame.duration);
		matrix = matrix * DMathLib::translate(Matrix4F(1.0f), ((before.positionFrame.vector + delta) * (after.positionFrame.vector - before.positionFrame.vector)));

		/* Calculate Scaling Matrix */
		delta = (frameTime - before.scaleFrame.duration) / (after.scaleFrame.duration - before.scaleFrame.duration);
		matrix = matrix * DMathLib::scale(Matrix4F(1.0f), ((before.scaleFrame.vector + delta) * (after.scaleFrame.vector - before.scaleFrame.vector)));

		return matrix;
	}
}
