// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AssimpWrapper.h"

#include "Animation/Objects/AnimNodeGraph.h"
#include "Core/Math/MathFunctions.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Dynamik
{
	/*
	 Assimp Importer object.
	*/
	Assimp::Importer localImporter;

	/*
	 Return the correct readable size of a given container.
	*/
	template<class TYPE>
	UI64 getCorrectSize(const UI64 size)
	{
		if (size < sizeof(TYPE))
			return size;

		return sizeof(TYPE);
	}

	/*
	 Load data from an aiMatrix4x4 object to a Matrix4F object.

	 @param mat: The aiMatrix4x4 object.
	*/
	Matrix4F aiMatrixToMatrix4F(const aiMatrix4x4& mat)
	{
		return Matrix4F(
			mat.a1, mat.a2, mat.a3, mat.a4,
			mat.b1, mat.b2, mat.b3, mat.b4,
			mat.c1, mat.c2, mat.c3, mat.c4,
			mat.d1, mat.d2, mat.d3, mat.d4);
	}

	/*
	 Load data from aiVectorKey to Vector3F object.

	 @param key: aiVectorKey object.
	*/
	Vector3F aiVectorKeyToVector3F(const aiVectorKey& key)
	{
		return Vector3F(key.mValue.x, key.mValue.y, key.mValue.z);
	}

	/*
	 Load data from aiQuatKey to Quaternion object.

	 @param key: aiQuatKey object.
	*/
	Quaternion aiQuatKeyToQuaternion(const aiQuatKey& key)
	{
		return Quaternion(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
	}

	DMKStaticMeshComponent AssimpWrapper::loadMeshComponent(VPTR pAiMeshObject, const DMKVertexLayout& vertexLayout)
	{
		auto _mesh = (aiMesh*)pAiMeshObject;

		DMKStaticMeshComponent _meshComponent;
		_meshComponent.vertexBuffer.initialize(_mesh->mNumVertices, vertexLayout);
		UI64 vertexOffset = 0;
		UI64 dataSize = 0;

		for (UI32 _index = 0; _index < _mesh->mNumVertices; _index++)
		{
			for (auto attribute : vertexLayout.attributes)
			{
				dataSize = (UI64)attribute.dataType * attribute.dataCount;

				switch (attribute.attributeType)
				{
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
					if (_mesh->HasPositions())
						_meshComponent.vertexBuffer.addData(&_mesh->mVertices[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
					if (_mesh->HasNormals())
						_meshComponent.vertexBuffer.addData(&_mesh->mNormals[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0:
					if (_mesh->HasVertexColors(0))
						_meshComponent.vertexBuffer.addData(&_mesh->mColors[0][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_1:
					if (_mesh->HasVertexColors(1))
						_meshComponent.vertexBuffer.addData(&_mesh->mColors[1][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_2:
					if (_mesh->HasVertexColors(2))
						_meshComponent.vertexBuffer.addData(&_mesh->mColors[2][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_3:
					if (_mesh->HasVertexColors(3))
						_meshComponent.vertexBuffer.addData(&_mesh->mColors[3][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0:
					if (_mesh->HasTextureCoords(0))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[0][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_1:
					if (_mesh->HasTextureCoords(1))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[1][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_2:
					if (_mesh->HasTextureCoords(2))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[2][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_3:
					if (_mesh->HasTextureCoords(3))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[3][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_4:
					if (_mesh->HasTextureCoords(4))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[4][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_5:
					if (_mesh->HasTextureCoords(5))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[5][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_6:
					if (_mesh->HasTextureCoords(6))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[6][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_7:
					if (_mesh->HasTextureCoords(7))
						_meshComponent.vertexBuffer.addData(&_mesh->mTextureCoords[7][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TANGENT:
					if (_mesh->HasTangentsAndBitangents())
						_meshComponent.vertexBuffer.addData(&_mesh->mTangents[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BITANGENT:
					if (_mesh->HasTangentsAndBitangents())
						_meshComponent.vertexBuffer.addData(&_mesh->mBitangents[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
					/* TODO */
					_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY:
					/* TODO */
					_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID:
					/* TODO */
					_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT:
					/* TODO */
					_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
					/* TODO */
					_meshComponent.vertexBuffer.setNull(dataSize, vertexOffset);
					break;

				default:
					DMK_ERROR_BOX("Invalid vertex attribute!");
					break;
				}

				vertexOffset += dataSize;
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

		return _meshComponent;
	}

	DMK_FORCEINLINE void loadAllNodes(aiNode* pNode, DMKAnimNodeGraph* pGraph, UI64* pIndex, std::unordered_map<STRING, UI64>* pNodeMap, Matrix4F parentWorldTransform = Matrix4F(1.0))
	{
		UI64 myIndex = (*pIndex)++;
		(*pNodeMap).insert({ pNode->mName.data, myIndex });

		DMKAnimNode node(myIndex, pNode->mName.C_Str(), aiMatrixToMatrix4F(pNode->mTransformation));
		node.setWorldTransform(DMathLib::multiply(node.getNodeMatrix(), parentWorldTransform));
		pGraph->addNode(node);

		for (UI32 i = 0; i < pNode->mNumChildren; i++)
			pGraph->nodes[myIndex].addChildNodeIndex(*pIndex),
			loadAllNodes(pNode->mChildren[i], pGraph, pIndex, pNodeMap, node.getWorldTransform());
	}

	DMK_FORCEINLINE DMKAnimKeyFrame getAnimationFrame(aiNodeAnim* pNodeAnim)
	{
		DMKAnimKeyFrame frame;

		for (UI32 transformIndex = 0; transformIndex < pNodeAnim->mNumPositionKeys; transformIndex++)
		{
			frame.timeStamp = pNodeAnim->mPositionKeys[transformIndex].mTime;
		}

		return frame;
	}

	DMK_FORCEINLINE void getBoneOffsetData(aiScene* pScene, aiNode* pNode, DMKAnimNodeGraph* pGraph, Matrix4F parentNodeTransform)
	{
		Matrix4F currentNodeTransform = DMathLib::multiply(aiMatrixToMatrix4F(pNode->mTransformation), parentNodeTransform);

		for (UI32 i = 0; i < pNode->mNumMeshes; i++)
		{
			aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];

			for (UI32 index = 0; index < pMesh->mNumBones; index++)
			{
				aiBone* pBone = pMesh->mBones[index];

				Matrix4F offsetMat = aiMatrixToMatrix4F(pBone->mOffsetMatrix);
				pGraph->getNode(pBone->mName.data).setWorldTransform(currentNodeTransform);
				DMathLib::multiply(offsetMat, currentNodeTransform);
			}
		}

		/* Recurse through all the children */
		for (UI32 i = 0; i < pNode->mNumChildren; i++)
			getBoneOffsetData(pScene, pNode->mChildren[i], pGraph, currentNodeTransform);
	}

	DMK_FORCEINLINE void loadNodeTransform(aiNode* pNode, Matrix4F parentWorldTransform, I32 parentBoneIndex, DMKAnimNodeGraph* pGraph)
	{
		Matrix4F currentLocalTransform = aiMatrixToMatrix4F(pNode->mTransformation);
		Matrix4F currentNodeWorldTransform = DMathLib::multiply(aiMatrixToMatrix4F(pNode->mTransformation), parentWorldTransform);

		if (parentBoneIndex >= 0)
		{
			pGraph->getNode(pNode->mName.data);
		}
	}

	DMKAnimation AssimpWrapper::loadAnimation(VPTR pAiAnimation, VPTR pAiRootNode)
	{
		auto pAnimation = (aiAnimation*)pAiAnimation;

		DMKAnimation animation;

		for (UI32 index = 0; index < pAnimation->mNumChannels; index++)
			animation.frames.pushBack(getAnimationFrame(pAnimation->mChannels[index]));

		animation.duration = pAnimation->mDuration;

		return animation;
	}

	DMKAnimatedMeshComponent AssimpWrapper::loadAnimatedMeshComponent(VPTR pAiSceneObject, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
	{
		auto _scene = (aiScene*)pAiSceneObject;

		if (!_scene)
		{
			DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
			return DMKAnimatedMeshComponent();
		}

		UI32 totalNodes = 0;
		UI64 vertexOffset = 0;

		DMKAnimatedMeshComponent animMeshComponent;

		/* Load all nodes/ bones */
		UI64 baseIndex = 0;
		loadAllNodes(_scene->mRootNode, &animMeshComponent.nodeGraph, &baseIndex, &animMeshComponent.nodeMap);

		/* Process mesh data */
		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
		{
			auto _mesh = _scene->mMeshes[_itr];

			/* Load Mesh Data */
			animMeshComponent.skinnedMesh = loadMeshComponent(_mesh, vertexLayout);

			for (UI32 boneIndex = 0; boneIndex < _mesh->mNumBones; boneIndex++)
			{
				aiBone* pBone = _mesh->mBones[boneIndex];

				for (UI32 i = 0; i < nodesPerVertex; i++)
				{
					animMeshComponent.nodeGraph.nodes[animMeshComponent.nodeMap[pBone->mName.data]].addVertexData(
						vertexOffset + pBone->mWeights[i].mVertexId, pBone->mWeights[i].mWeight);

					UI64 vertexID = vertexOffset + pBone->mWeights[i].mVertexId;
					animMeshComponent.skinnedMesh.vertexBuffer.updateVertexAttribute(vertexID, nullptr, DMKVertexAttributeType());
				}
			}

			vertexOffset += animMeshComponent.skinnedMesh.vertexBuffer.size();
		}

		for (UI32 index = 0; index < _scene->mNumAnimations; index++)
			animMeshComponent.animations.pushBack(loadAnimation(_scene->mAnimations[index], _scene->mRootNode));

		return animMeshComponent;
	}

	DMKAnimatedMeshComponent AssimpWrapper::loadAnimatedModel(const STRING& file, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
	{
		return loadAnimatedMeshComponent((VPTR)localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs), vertexLayout, nodesPerVertex);
	}

	ARRAY<DMKStaticMeshComponent> AssimpWrapper::loadStaticModel(const STRING& file, const DMKVertexLayout& vertexLayout)
	{
		auto _scene = localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!_scene)
		{
			DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
			return ARRAY<DMKStaticMeshComponent>();
		}

		ARRAY<DMKStaticMeshComponent> myModel;
		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
			myModel.pushBack(loadMeshComponent(_scene->mMeshes[_itr], vertexLayout));

		return myModel;
	}
}