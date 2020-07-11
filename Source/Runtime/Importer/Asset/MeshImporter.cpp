// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshImporter.h"

#include "Core/Components/RenderableComponents/StaticMeshComponent.h"
#include "Core/Objects/Resource/Primitives.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

	ARRAY<DMKStaticMeshComponent> DMKMeshImporter::loadMeshes(const STRING& path, const DMKVertexLayout& vertexLayout)
	{
		static Assimp::Importer _importer;
		static auto _scene = _importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!_scene)
		{
			DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
			return ARRAY<DMKStaticMeshComponent>();
		}

		ARRAY<DMKStaticMeshComponent> _myMeshes;
		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
		{
			auto _mesh = _scene->mMeshes[_itr];

			DMKStaticMeshComponent _meshComponent;
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

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
						if (_mesh->HasNormals())
							copyData(vertexPointer.get(), std::move(_mesh->mNormals[_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0:
						if (_mesh->HasVertexColors(0))
							copyData(vertexPointer.get(), std::move(_mesh->mColors[0][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_1:
						if (_mesh->HasVertexColors(1))
							copyData(vertexPointer.get(), std::move(_mesh->mColors[1][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_2:
						if (_mesh->HasVertexColors(2))
							copyData(vertexPointer.get(), std::move(_mesh->mColors[2][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_3:
						if (_mesh->HasVertexColors(3))
							copyData(vertexPointer.get(), std::move(_mesh->mColors[3][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0:
						if (_mesh->HasTextureCoords(0))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[0][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_1:
						if (_mesh->HasTextureCoords(1))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[1][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_2:
						if (_mesh->HasTextureCoords(2))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[2][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_3:
						if (_mesh->HasTextureCoords(3))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[3][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_4:
						if (_mesh->HasTextureCoords(4))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[4][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_5:
						if (_mesh->HasTextureCoords(5))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[5][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_6:
						if (_mesh->HasTextureCoords(6))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[6][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_7:
						if (_mesh->HasTextureCoords(7))
							copyData(vertexPointer.get(), std::move(_mesh->mTextureCoords[7][_index]), attributeSize);
						else
							DMKMemoryFunctions::setData(vertexPointer.get(), 0, attributeSize);
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TANGENT:
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BITANGENT:
						break;

					case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
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

	void DMKMeshImporter::unloadMesh(const ARRAY<DMKStaticMeshComponent>& meshes)
	{
		for (UI32 index = 0; index < meshes.size(); index++)
		{
			StaticAllocator<BYTE>::deallocate(meshes[index].vertexBuffer, meshes[index].vertexCount * meshes[index].vertexLayout.getVertexSize());
		}
	}
}