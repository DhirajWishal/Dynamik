// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/VertexBufferObject.h"
#include "Core/Hash/Hasher.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace GraphicsCore
	{
		UI64 VertexBufferObject::LayoutHash() const
		{
			return Hasher::GetHash(mAttributes.data(), sizeof(VertexAttribute) * mAttributes.size());
		}

		UI64 VertexBufferObject::LayoutSize() const
		{
			UI64 size = 0;
			for (auto itr = mAttributes.begin(); itr != mAttributes.end(); itr++)
				size += itr->Size();

			return size;
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

		void VertexBufferObject::Initialize()
		{
			// Check if the data store is allocated.
			if (pDataStore)
			{
				Logger::LogWarn(TEXT("The vertex buffer object is already initialized! Reinitializing it with new data."));
				delete pDataStore;
			}

			mSize = LayoutSize();
			pDataStore = operator new (mSize);
		}

		void VertexBufferObject::Terminate()
		{
			// Check and delete data.
			if (pDataStore)
				delete pDataStore;

			mAttributes.clear();
			mSize = 0;
		}
	}
}