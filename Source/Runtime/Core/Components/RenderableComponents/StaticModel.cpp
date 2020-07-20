// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "StaticModel.h"

namespace Dynamik
{
	void DMKStaticModel::addMesh(const DMKStaticMeshComponent& staticMesh)
	{
		staticMeshes.pushBack(staticMesh);
	}

	DMKStaticMeshComponent& DMKStaticModel::getMesh(I64 index)
	{
		return staticMeshes[index];
	}

	UI64 DMKStaticModel::getMeshCount() const
	{
		return staticMeshes.size();
	}

	void DMKStaticModel::setPosition(const Vector3F& position)
	{
		for (UI64 index = 0; index < staticMeshes.size(); index++)
			staticMeshes[index].setPosition(position);
	}

	void DMKStaticModel::setScale(const Vector3F& scale)
	{
		for (UI64 index = 0; index < staticMeshes.size(); index++)
			staticMeshes[index].setScale(scale);
	}

	void DMKStaticModel::setRotation(const Quaternion& rotation)
	{
		for (UI64 index = 0; index < staticMeshes.size(); index++)
			staticMeshes[index].setRotation(rotation);
	}
}
