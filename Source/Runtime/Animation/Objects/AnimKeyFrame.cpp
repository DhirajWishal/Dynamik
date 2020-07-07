// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimKeyFrame.h"

namespace Dynamik
{
	F32 DMKAnimKeyFrame::getTimeStamp() const
	{
		return timeStamp;
	}

	DMKAnimNodeTransform DMKAnimKeyFrame::getNodeTransform(const STRING& name) const
	{
		return transform[name];
	}
	
	std::unordered_map<STRING, DMKAnimNodeTransform> DMKAnimKeyFrame::getTransformMap() const
	{
		return transform;
	}
}
