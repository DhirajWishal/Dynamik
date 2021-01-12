// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/Uniform.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void Uniform::AddAttribute(const char* pName, DataType mDatType, UI64 layerCount)
		{
			// Create the uniform attribute.
			UniformAttribute mAttribute = {};
			mAttribute.mDataType = mDatType;
			mAttribute.mLayerCount = layerCount;
			mAttribute.mOffset = mSize;

			// Update the uniform size.
			mSize += mAttribute.Size();

			// Add the attribute to the map.
			mAttributeMap[pName] = std::move(mAttribute);
		}

		void* Uniform::GetAttributeLocation(const char* pName, UI64 layer)
		{
			// Check if the attribute is available in the uniform.
			if (mAttributeMap.find(pName) == mAttributeMap.end())
				return nullptr;

			// Get the attribute and return its pointer.
			auto& mAttribute = mAttributeMap[pName];
			return reinterpret_cast<void*>(reinterpret_cast<UI64>(pDataStore) + (mAttribute.mOffset + (mAttribute.GetTypeSize() * layer)));
		}

		void Uniform::Initialize()
		{
			// Check if the uniform is initialized.
			if (pDataStore)
			{
				Logger::LogWarn(TEXT("The uniform is already initialized! Updating the data uniform with the new values (if added)."));
				delete pDataStore;
			}

			// Check if the uniform is valid.
			if (!mSize && mType == UniformType::UNIFORM_BUFFER)
			{
				DMK_LOG_ERROR(TEXT("Unable to initialize the uniform! The size of the uniform is invalid."));
				return;
			}

			// Allocate the new block.
			pDataStore = operator new (mSize);
		}

		void Uniform::Terminate()
		{
			// Terminate the store if allocated.
			if (pDataStore)
				delete pDataStore;

			// Clear the attribute map.
			mAttributeMap.clear();
		}
	}
}