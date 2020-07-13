// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNode.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void AAnimNodeData::add(const UI32& vertexID, const F32& weight)
	{
		vertexIDs.pushBack(vertexID);
		weights.pushBack(weight);
	}
	
	void DMKAnimNode::addChildNodeIndex(UI64 iIndex)
	{
		childNodeIndexes.pushBack(iIndex);
	}
	
	Matrix4F DMKAnimNode::getAnimatedTransform() const
	{
		return animatedTransform;
	}
	
	void DMKAnimNode::setAnimatedTransform(const Matrix4F& transform)
	{
		animatedTransform = transform;
	}
	
	void DMKAnimNode::calculateInverseBindTransform(const Matrix4F& parentBindTransform)
	{
		auto bindTransform = parentBindTransform * localTransform;
		inverseBindTransform = DMathLib::inverse(bindTransform);
	}
}
