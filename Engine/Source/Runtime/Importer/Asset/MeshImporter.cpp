// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshImporter.h"

#include "ComponentSystem/Components/RenderableComponents/MeshComponent.h"
#include "Object/Resource/Primitives.h"

#include <assimp/assimp/Importer.hpp>
#include <assimp/assimp/scene.h>
#include <assimp/assimp/postprocess.h>

namespace Dynamik
{
	DMKVertexBufferDescriptor getVertexBufferDescriptor(POINTER<aiMesh> mesh)
	{
		DMKVertexBufferDescriptor _descriptor;

		DMKShaderInputAttribute _attribute;
		_attribute.dataCount = 1;
		_attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		if (mesh->HasPositions())
		{
			_attribute.attributeType = DMKShaderInputAttributeType::DMK_SHADER_INPUT_ATTRIBUTE_TYPE_POSITION;
			_descriptor.attributes.pushBack(_attribute);
		}
		if (mesh->HasVertexColors(0))
		{
			_attribute.attributeType = DMKShaderInputAttributeType::DMK_SHADER_INPUT_ATTRIBUTE_TYPE_COLOR;
			_descriptor.attributes.pushBack(_attribute);
		}
		if (mesh->HasTextureCoords(0))
		{
			_attribute.attributeType = DMKShaderInputAttributeType::DMK_SHADER_INPUT_ATTRIBUTE_TYPE_TEXTURE_COORDINATES;
			_descriptor.attributes.pushBack(_attribute);
		}
		if (mesh->HasNormals())
		{
			_attribute.attributeType = DMKShaderInputAttributeType::DMK_SHADER_INPUT_ATTRIBUTE_TYPE_NORMAL;
			_descriptor.attributes.pushBack(_attribute);
		}

		return _descriptor;
	}

	ARRAY<DMKMeshComponent> DMKMeshImporter::loadMeshes(const STRING& path)
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
			DMKMeshComponent _meshComponent;
			auto _mesh = _scene->mMeshes[_itr];

			DMKVertexObject _object;
			_meshComponent.vertexDescriptor = getVertexBufferDescriptor(_mesh);
			for (UI32 _index = 0; _index < _mesh->mNumVertices; _index++)
			{
				if (_mesh->HasPositions())
				{
					_object.position.load(&_mesh->mVertices[_index].x);
				}
				else _object.position = { 0.0f, 0.0f, 0.0f };

				if (_mesh->HasVertexColors(0))
				{
					_object.color.load(&_mesh->mColors[0][_index].r);
				}
				else _object.color = { 1.0f, 1.0f, 1.0f };

				if (_mesh->HasTextureCoords(0))
				{
					_object.textureCoord.load(&_mesh->mTextureCoords[0][_index].x);
				}
				else _object.textureCoord = { 0.0f, 0.0f, 0.0f };

				if (_mesh->HasNormals())
				{
					_object.normal.load(&_mesh->mNormals[_index].x);
				}
				else _object.normal = { 0.0f, 0.0f, 0.0f };

				if (_mesh->HasBones())
				{
				}

				_meshComponent.rawVertexBufferObject.pushBack(_object);
			}

			aiFace face;
			for (UI32 index = 0; index < _mesh->mNumFaces; index++)
			{
				face = _mesh->mFaces[index];
				for (UI32 itr = 0; itr < face.mNumIndices; itr++)
					_meshComponent.indexBufferObject.pushBack(face.mIndices[itr]);
			}

			_myMeshes.pushBack(_meshComponent);
		}

		return _myMeshes;
	}

	void DMKMeshImporter::unloadMesh(const ARRAY<DMKMeshComponent>& meshes)
	{
	}
}