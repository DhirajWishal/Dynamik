#include "dmkafx.h"
#include "MeshComponent.h"

#include "Memory/MemoryFunctions.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	/* Get the vertex buffer object byte size */
	UI32 DMKMeshComponent::getVertexBufferObjectByteSize()
	{
		return vertexDescriptor.getVertexSize() * rawVertexBufferObject.size();
	}

	/* Get the index buffer object byte size */
	UI32 DMKMeshComponent::getIndexBufferObjectByteSize()
	{
		return (UI32)indexBufferType * indexBufferObject.size();
	}

	/* Pack data to a given location. That location must be pre allocated */
	void DMKMeshComponent::packData(VPTR location)
	{
		POINTER<BYTE> _nextPtr = location;

		for (auto vertex : rawVertexBufferObject)
		{
			for (auto attribute : vertexDescriptor.attributes)
			{
				auto _byteSize = ((UI32)attribute.dataType * attribute.dataCount);
				switch (attribute.attributeType)
				{
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.position, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.color, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.textureCoord, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.uvCoord, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.normal, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_SINTEGRITY:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.integrity, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.boneInformation->boneIDs, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT:
					MemoryFunctions::moveData(_nextPtr.get(), &vertex.boneInformation->boneWeights, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
					DMK_ERROR("Dynamik does not support custom vertex attributes yet!");
					break;
				default:
					DMK_FATAL("Invalid Vertex Attribute!");
					break;
				}

				_nextPtr += _byteSize / sizeof(F32);
			}
		}
	}

	ARRAY<DMKMeshComponent> DMKMeshComponent::create(STRING path, ARRAY<DMKUniformDescription> uniformDescriptors)
	{
		auto mesh = DMKMeshImporter::loadMeshes(path);

		for (UI32 index = 0; index < mesh.size(); index++)
		{
			for (auto _description : uniformDescriptors)
			{
				DMKUniformBufferObject _ubo;
				_ubo.myDescription = _description;
				mesh[index].uniformBUfferObjects.pushBack(_ubo);
			}
		}

		return mesh;
	}

	ARRAY<DMKMeshComponent> DMKMeshComponent::create(ARRAY<DMKVertexObject> vertexData, ARRAY<UI32> indexData, DMKVertexBufferDescriptor vertexDescription, ARRAY<DMKUniformDescription> uniformDescriptors)
	{
		DMKMeshComponent _mesh;
		_mesh.rawVertexBufferObject = vertexData;
		_mesh.vertexDescriptor = vertexDescription;
		_mesh.indexBufferObject = indexData;
		_mesh.indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;
		for (auto _description : uniformDescriptors)
		{
			DMKUniformBufferObject _object;
			_object.myDescription = _description;
			_mesh.uniformBUfferObjects.pushBack(_object);
		}

		return { _mesh };
	}
}