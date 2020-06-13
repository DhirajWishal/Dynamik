// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshComponent.h"

#include "Memory/MemoryFunctions.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	/* Get the vertex buffer object byte size */
	UI64 DMKMeshComponent::getVertexBufferObjectByteSize()
	{
		return vertexDescriptor.getVertexSize() * rawVertexBufferObject.size();
	}

	/* Get the index buffer object byte size */
	UI64 DMKMeshComponent::getIndexBufferObjectByteSize()
	{
		return (UI64)indexBufferType * indexBufferObject.size();
	}

	/* Pack data to a given location. That location must be pre allocated */
	void DMKMeshComponent::packData(VPTR location)
	{
		POINTER<BYTE> _nextPtr = location;
		UI64 _byteSize = 0;

		for (auto vertex : rawVertexBufferObject)
		{
			for (auto attribute : vertexDescriptor.attributes)
			{
				_byteSize = ((UI64)attribute.dataType * attribute.dataCount);
				switch (attribute.attributeType)
				{
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.position, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.color, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.textureCoord, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.uvCoord, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.normal, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.integrity, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.boneInformation->boneIDs, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT:
					DMKMemoryFunctions::moveData(_nextPtr.get(), &vertex.boneInformation->boneWeights, _byteSize);
					break;
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
					DMK_ERROR("Dynamik does not support custom vertex attributes yet!");
					break;
				default:
					DMK_FATAL("Invalid Vertex Attribute!");
					break;
				}

				_nextPtr += _byteSize;
			}
		}
	}

	void DMKMeshComponent::setMatrix(const MAT4F& matrix)
	{
		modelMatrix = matrix;
	}

	void DMKMeshComponent::update(const MAT4F& matrix)
	{
		modelMatrix = matrix;
	}

	MAT4F DMKMeshComponent::getMatrix()
	{
		return modelMatrix;
	}

	DMKMeshComponent::operator MAT4F() const
	{
		return this->modelMatrix;
	}

	ARRAY<DMKMeshComponent> DMKMeshComponent::create(STRING path)
	{
		auto mesh = DMKMeshImporter::loadMeshes(path);

		return mesh;
	}

	ARRAY<DMKMeshComponent> DMKMeshComponent::create(ARRAY<DMKVertexObject> vertexData, ARRAY<UI32> indexData, DMKVertexBufferDescriptor vertexDescription)
	{
		DMKMeshComponent _mesh;
		_mesh.rawVertexBufferObject = vertexData;
		_mesh.vertexDescriptor = vertexDescription;
		_mesh.indexBufferObject = indexData;
		_mesh.indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;

		return { _mesh };
	}
	
	void DMKMeshComponent::_initializeUniformBufferDescription()
	{
		//addUniformBufferDescription(DMKUniformBufferObject::createUniformModel());
	}
}