// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Mesh/StaticMesh.h"

namespace DMK
{
	namespace GraphicsCore
	{
		PrimitveBuffer StaticMesh::GetVertexBuffer()
		{
			return PrimitveBuffer();
		}

		PrimitveBuffer StaticMesh::GetIndexBuffer()
		{
			return PrimitveBuffer();
		}

		void StaticMesh::AddUniformBuffer(const UniformBuffer& uBuffer)
		{
		}

		UniformBuffer* StaticMesh::GetUniformBuffer(UI64 index) const
		{
			return nullptr;
		}
	}
}