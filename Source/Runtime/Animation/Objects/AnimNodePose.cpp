// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNodePose.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	Matrix4F DMKAnimNodePose::interpolate(DMKAnimNodePose oldPose, F32 frameTime)
	{
		Matrix4F matrix = Matrix4F(1.0f);
		F32 delta = (frameTime - oldPose.duration) / (this->duration - oldPose.duration);

		/* Calculate Rotation Matrix */
		matrix = matrix * DMathLib::toRotationalMatrix(DMathLib::interpolate(this->rotation, oldPose.rotation, delta));

		/* Calculate Translation Matrix */
		matrix = matrix * DMathLib::translate(Matrix4F(1.0f), ((oldPose.position + delta) * (this->position - oldPose.position)));

		/* Calculate Scaling Matrix */
		matrix = matrix * DMathLib::scale(Matrix4F(1.0f), ((oldPose.scale + delta) * (this->scale - oldPose.scale)));

		return matrix;
	}
	
	Matrix4F DMKAnimNodePose::getMatrix()
	{
		Matrix4F matrix = Matrix4F::Identity;
		matrix = matrix * DMathLib::toRotationalMatrix(rotation);
		matrix = matrix * DMathLib::translate(Matrix4F::Identity, position);
		matrix = matrix * DMathLib::scale(Matrix4F::Identity, scale);

		return matrix;
	}
}
