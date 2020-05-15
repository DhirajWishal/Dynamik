#include "dmkafx.h"
#include "MeshComponent.h"

#include "Memory/MemoryFunctions.h"

namespace Dynamik
{
	UI32 DMKMeshComponent::getVertexBufferObjectByteSize()
	{
		return vertexDescriptor.getVertexSize() * rawVertexBufferObject.size();
	}

	UI32 DMKMeshComponent::getIndexBufferObjectByteSize()
	{
		return (UI32)indexBufferType * indexBufferObject.size();
	}
	
	void DMKMeshComponent::packData(const DMKVertexBufferDescriptor& descriptor, VPTR location)
	{
		POINTER<BYTE> _nextPtr = location;

		for (auto vertex : rawVertexBufferObject)
		{
			for (auto attribute : descriptor.attributes)
			{
				switch (attribute.attributeType)
				{
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.position, (UI32)attribute.dataType);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.color, (UI32)attribute.dataType);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.textureCoord, (UI32)attribute.dataType);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.normal, (UI32)attribute.dataType);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.integrity, (UI32)attribute.dataType);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
					DMK_ERROR("Dynamik does not support custom vertex attributes yet!");
					break;
				default:
					DMK_FATAL("Invalid Vertex Attribute!");
					break;
				}

				_nextPtr += (UI32)attribute.dataType / sizeof(F32);
			}
		}
	}
}