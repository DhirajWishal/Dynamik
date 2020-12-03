// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/VertexBufferObject.h"
#include "Core/Hash/Hasher.h"

namespace DMK
{
	namespace GraphicsCore
	{
		UI64 VertexBufferObject::LayoutHash() const
		{
			return Hasher::GetHash(mAttributes.data(), sizeof(VertexAttribute) * mAttributes.size());
		}
		
		void VertexBufferObject::AddAttribute(VertexAttributeType type, DataType dataType, UI64 layerCount)
		{
			mAttributes.insert(mAttributes.end(), VertexAttribute(type, dataType, layerCount));
		}

		void VertexBufferObject::SetAttributes(const std::vector<VertexAttribute>& attributes)
		{
			mAttributes = attributes;
		}

		void VertexBufferObject::SetAttributes(std::vector<VertexAttribute>&& attributes)
		{
			mAttributes = attributes;
		}
	}
}