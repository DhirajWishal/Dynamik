// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshImporter.h"

#include "ComponentSystem/Components/RenderableComponents/MeshComponent.h"
#include "Core/Object/Resource/Primitives.h"

#include <assimp/assimp/Importer.hpp>
#include <assimp/assimp/scene.h>
#include <assimp/assimp/postprocess.h>

namespace Dynamik
{
	/*
	 Utility function to copy data from source to destination using a byte count.
	 This also checks for runtime errors (if the size of the source is less than or equal to the byte count).
	*/
	template<class TYPE>
	void DMK_FORCEINLINE copyData(VPTR dst, TYPE&& src, UI64 byteCount)
	{
		if (byteCount < sizeof(TYPE))
			DMKMemoryFunctions::moveData(dst, &src, byteCount);
		else
			DMKMemoryFunctions::moveData(dst, &src, sizeof(TYPE));
	}

	ARRAY<DMKMeshComponent> DMKMeshImporter::loadMeshes(const STRING& path, const DMKVertexLayout& vertexLayout)
	{
		static Assimp::Importer _importer;
		static auto _scene = _importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!_scene)
		{
			DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
			return ARRAY<DMKMeshComponent>();
		}

		ARRAY<DMKMeshComponent> _myMeshes;
		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
		{
			auto _mesh = _scene->mMeshes[_itr];

			DMKMeshComponent _meshComponent;
			_meshComponent.vertexLayout = vertexLayout;
			_meshComponent.vertexBuffer = StaticAllocator<BYTE>::rawAllocate(vertexLayout.getVertexSize() * _mesh->mNumVertices);
			_meshComponent.vertexCount = _mesh->mNumVertices;
			POINTER<BYTE> vertexPointer = _meshComponent.vertexBuffer;
			UI64 attributeSize = 0;

			for (UI32 _index = 0; _index < _mesh->mNumVertices; _index++)
			{
				for (auto attribute : vertexLayout.attributes)
				{
					attributeSize = (UI64)attribute.dataType * attribute.dataCount;

					switch (attribute.attributeType)
					{
					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
						if (_mesh->HasPositions())
							copyData(vertexPointer.get(), std::move(_mesh->mVertices[_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR:
						if (_mesh->HasVertexColors(0))
							copyData(vertexPointer.get(), std::move(_mesh->mColors[0][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES:
						if (_mesh->HasTextureCoords(0))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[0][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
						if (_mesh->HasNormals())
							copyData(vertexPointer.get(), std::move(_mesh->mNormals[_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY:
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID:
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT:
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
						break;

					default:
						DMK_ERROR_BOX("Invalid vertex attribute!");
						break;
					}

					vertexPointer += attributeSize;
				}
			}

			aiFace face;
			for (UI32 index = 0; index < _mesh->mNumFaces; index++)
			{
				face = _mesh->mFaces[index];
				for (UI32 itr = 0; itr < face.mNumIndices; itr++)
					_meshComponent.indexBuffer.pushBack(face.mIndices[itr]);
			}

			_meshComponent.indexCount = _meshComponent.indexBuffer.size();
			_myMeshes.pushBack(_meshComponent);
		}

		return _myMeshes;
	}

	void DMKMeshImporter::unloadMesh(const ARRAY<DMKMeshComponent>& meshes)
	{
		for (UI32 index = 0; index < meshes.size(); index++)
		{
			StaticAllocator<BYTE>::deallocate(meshes[index].vertexBuffer, meshes[index].vertexCount * meshes[index].vertexLayout.getVertexSize());
		}
	}
}