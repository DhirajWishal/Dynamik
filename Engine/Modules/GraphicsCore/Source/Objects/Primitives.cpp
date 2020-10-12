// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/Primitives.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void UniformBuffer::AddAttribute(const STRING& name, UI64 size)
		{
			UniformAttribute attribute;
			attribute.byteSize = size;
			attribute.offset = this->size;
			attributeMap[name] = attribute;

			this->size += size;
		}

		void UniformBuffer::Initialize()
		{
			if (!size)
				return;

			pDataStore = operator new (size);
		}

		void UniformBuffer::Terminate()
		{
			delete pDataStore;
		}

		std::vector<UniformBuffer::UniformAttribute> UniformBuffer::GetAttributes() const
		{
			std::vector<UniformBuffer::UniformAttribute> attributes;

			// Iterate through the attribute map and retrieve all the attributes. 
			for (auto itr = attributeMap.begin(); itr != attributeMap.end(); itr++)
				attributes.push_back(itr->second);

			return attributes;
		}
	}
}