// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNodeTransform.h"

namespace Dynamik
{
	void DMKAnimNodeTransform::addPose(const DMKAnimNodePose& pose)
	{
		nodePoses.pushBack(pose);
	}
	
	Matrix4F DMKAnimNodeTransform::getInterpolation(UI64 currentPose, UI64 nextPose, F32 frameTime)
	{
		return nodePoses[currentPose].interpolate(nodePoses[nextPose], frameTime);
	}
}