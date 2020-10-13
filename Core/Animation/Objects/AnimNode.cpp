// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNode.h"

#include "Core/Math/MathFunctions.h"

void DMKAnimNode::setOffsetMatrix(const Matrix4F& mat)
{
	offsetMatrix = mat;
}

Matrix4F DMKAnimNode::getOffsetMatrix()
{
	return offsetMatrix;
}

void DMKAnimNode::setNodeMatrix(const Matrix4F& mat)
{
	nodeMatrix = mat;
}

Matrix4F DMKAnimNode::getNodeMatrix()
{
	return nodeMatrix;
}

void DMKAnimNode::setWorldTransform(const Matrix4F& mat)
{
	worldTransform = mat;
}

Matrix4F DMKAnimNode::getWorldTransform()
{
	return worldTransform;
}

void DMKAnimNode::addChildNodeIndex(const UI64& index)
{
	childNodeIndexes.push_back(index);
}

void DMKAnimNode::addVertexData(const UI32& vertexID, const float& weight)
{
	vertexIDs.push_back(vertexID);
	weights.push_back(weight);
}
