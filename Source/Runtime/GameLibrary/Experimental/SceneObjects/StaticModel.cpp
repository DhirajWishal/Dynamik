// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "StaticModel.h"

namespace Dynamik
{
	namespace Experimental
	{
		void DMKStaticModel::loadModel(const STRING& asset, const DMKVertexLayout& vertexLayout, UI64 indexSize)
		{
		}

		const UI64 DMKStaticModel::getMeshCount()
		{
			return meshObjects.size();
		}

		DMKMeshObject* DMKStaticModel::getMeshObject(UI64 index)
		{
			return Cast<DMKMeshObject*>(meshObjects.location(index));
		}
	}
}
