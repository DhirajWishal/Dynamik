// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNode.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKAnimNode::setParentNode(DMKAnimNode* pAnimNode)
	{
		pParentNode = pAnimNode;
	}
	
	void DMKAnimNode::addChildNode(DMKAnimNode* pAnimNode)
	{
		pChildNodes.pushBack(pAnimNode);
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
