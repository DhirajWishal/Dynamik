// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AssimpWrapper.h"

#include <assimp/assimp/Importer.hpp>
#include <assimp/assimp/scene.h>
#include <assimp/assimp/postprocess.h>

namespace Dynamik
{
	/*
	 Assimp Importer object.
	*/
	Assimp::Importer localImporter;

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

	DMKMeshComponent AssimpWrapper::loadMeshComponent(VPTR pAiMeshObject, const DMKVertexLayout& vertexLayout)
	{
		auto _mesh = (aiMesh*)pAiMeshObject;

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

		return _meshComponent;
	}

	DMK_FORCEINLINE void readAllNodes(aiNode* pNode, ARRAY<DMKAnimNode>* pAnimNodes, const DMKAnimNode* pParentNode)
	{
		DMKAnimNode node(0, pNode->mName.C_Str(), aiMatrixToMatrix4F(pNode->mTransformation));
		node.pRootNode = (DMKAnimNode*)pParentNode;
		pAnimNodes->pushBack(node);

		auto makeRoot = pAnimNodes->location(-1);
		for (UI32 i = 0; i < pNode->mNumChildren; i++)
			readAllNodes(pNode->mChildren[i], pAnimNodes, makeRoot);
	}

	DMK_FORCEINLINE DMKAnimKeyFrame getAnimationFrame(aiNodeAnim* pNodeAnim)
	{
		DMKAnimKeyFrame frame;

		for (UI32 transformIndex = 0; transformIndex < pNodeAnim->mNumPositionKeys; transformIndex++)
		{
			DMKAnimNodeTransform transform(
				aiVectorKeyToVector3F(pNodeAnim->mPositionKeys[transformIndex]),
				aiQuatKeyToQuaternion(pNodeAnim->mRotationKeys[transformIndex]),
				aiVectorKeyToVector3F(pNodeAnim->mScalingKeys[transformIndex]));

			frame.timeStamp = pNodeAnim->mPositionKeys[transformIndex].mTime;
			frame.transform[pNodeAnim->mNodeName.C_Str()] = transform;
		}

		return frame;
	}

	DMKAnimation AssimpWrapper::loadAnimation(VPTR pAiAnimation, VPTR pAiRootNode)
	{
		auto pAnimation = (aiAnimation*)pAiAnimation;

		DMKAnimation animation;
		
		for (UI32 index = 0; index < pAnimation->mNumChannels; index++)
			animation.frames.pushBack(getAnimationFrame(pAnimation->mChannels[index]));
		
		animation.duration = pAnimation->mDuration;
		readAllNodes((aiNode*)pAiRootNode, &animation.nodes, nullptr);

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
		UI32 vertexOffset = 0;

		DMKAnimatedMeshComponent animMeshComponent;
		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
		{
			auto _mesh = _scene->mMeshes[_itr];

			animMeshComponent.nodeData = ARRAY<AAnimNodeData>(_mesh->mNumVertices);

			for (UI32 boneIndex = 0; boneIndex < _mesh->mNumBones; boneIndex++)
			{
				/* Create a new node structure to store the bone data */
				DMKAnimNode node;
				node.name = _mesh->mBones[boneIndex]->mName.data;
				_scene->mRootNode;

				if (animMeshComponent.nodeMap.find(node.name) == animMeshComponent.nodeMap.end())
				{
					node.index = totalNodes++;

					AAnimNodeInfo nodeInfo;
					animMeshComponent.nodeInfos.pushBack(nodeInfo);
				}
				else
					node.index = animMeshComponent.nodeMap[node.name];

				animMeshComponent.nodeMap[node.name] = node.index;
				animMeshComponent.nodeInfos[node.index].offset = aiMatrixToMatrix4F(_mesh->mBones[boneIndex]->mOffsetMatrix);


				for (UI32 i = 0; i < nodesPerVertex; i++)
				{
					UI32 vertexID = vertexOffset + _mesh->mBones[boneIndex]->mWeights[i].mVertexId;
					animMeshComponent.nodeData[vertexID].add(vertexID, _mesh->mBones[boneIndex]->mWeights[i].mWeight);
				}

			}

			animMeshComponent.skinnedMesh = loadMeshComponent(_mesh, vertexLayout);
			vertexOffset += animMeshComponent.skinnedMesh.vertexCount;
		}

		for (UI32 index = 0; index < _scene->mNumAnimations; index++)
			animMeshComponent.animations.pushBack(loadAnimation(_scene->mAnimations[index], _scene->mRootNode));

		return animMeshComponent;
	}

	DMKAnimatedMeshComponent AssimpWrapper::loadAnimatedModel(const STRING& file, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
	{
		return loadAnimatedMeshComponent((VPTR)localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs), vertexLayout, nodesPerVertex);
	}

	ARRAY<DMKMeshComponent> AssimpWrapper::loadStaticModel(const STRING& file, const DMKVertexLayout& vertexLayout)
	{
		auto _scene = localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!_scene)
		{
			DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
			return ARRAY<DMKMeshComponent>();
		}

		ARRAY<DMKMeshComponent> myModel;
		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
			myModel.pushBack(loadMeshComponent(_scene->mMeshes[_itr], vertexLayout));

		return myModel;
	}
}
