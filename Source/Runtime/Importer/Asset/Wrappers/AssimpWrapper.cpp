// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AssimpWrapper.h"

#include "Animation/Objects/AnimNodeGraph.h"
#include "Core/Math/MathFunctions.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <future>

namespace Dynamik
{
	/*
	 Return the correct readable size of a given container.
	*/
	template<class TYPE>
	DMK_FORCEINLINE UI64 getCorrectSize(const UI64 size)
	{
		if (size < sizeof(TYPE))
			return size;

		return sizeof(TYPE);
	}

	/*
	 Load data from an aiMatrix4x4 object to a Matrix4F object.

	 @param mat: The aiMatrix4x4 object.
	*/
	DMK_FORCEINLINE Matrix4F aiMatrixToMatrix4F(const aiMatrix4x4& mat)
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
	DMK_FORCEINLINE Vector3F aiVectorKeyToVector3F(const aiVectorKey& key)
	{
		return Vector3F(key.mValue.x, key.mValue.y, key.mValue.z);
	}

	/*
	 Load data from aiQuatKey to Quaternion object.

	 @param key: aiQuatKey object.
	*/
	DMK_FORCEINLINE Quaternion aiQuatKeyToQuaternion(const aiQuatKey& key)
	{
		return Quaternion(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
	}

	/*
	 Mesh load function.
	 This function loads all the data related to a specific mesh in the aiScene object. This function is intended to
	 be used in threads and thus improving the load times.

	 @param pAiMeshObject: The aiMeshObject in the aiScene object.
	 @param pAiScene: Th aiScene object.
	 @param vertexLayout: The vertex layout to load the vertex data.
	 @param pComponent: The mesh component pointer to load all the data to.
	*/
	DMK_FORCEINLINE void meshLoadFunction(VPTR pAiMeshObject, VPTR pAiScene, const DMKVertexLayout& vertexLayout, DMKMeshObject* pMeshObject)
	{
		auto _mesh = Cast<aiMesh*>(pAiMeshObject);
		auto _scene = Cast<aiScene*>(pAiScene);
		pMeshObject->setName(_mesh->mName.data);

		/* Resolve materials */
		aiString _texPath;
		aiMaterial* _material = nullptr;

		if (_scene->HasMaterials())
		{
			_material = _scene->mMaterials[_mesh->mMaterialIndex];

			_material->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &_texPath);

			auto tCount0 = _material->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
			auto tCount1 = _material->GetTextureCount(aiTextureType::aiTextureType_SPECULAR);
			auto tCount2 = _material->GetTextureCount(aiTextureType::aiTextureType_AMBIENT);
			auto tCount3 = _material->GetTextureCount(aiTextureType::aiTextureType_EMISSIVE);
			auto tCount4 = _material->GetTextureCount(aiTextureType::aiTextureType_HEIGHT);
			auto tCount5 = _material->GetTextureCount(aiTextureType::aiTextureType_NORMALS);
			auto tCount6 = _material->GetTextureCount(aiTextureType::aiTextureType_SHININESS);
			auto tCount7 = _material->GetTextureCount(aiTextureType::aiTextureType_OPACITY);
			auto tCount8 = _material->GetTextureCount(aiTextureType::aiTextureType_DISPLACEMENT);
			auto tCount9 = _material->GetTextureCount(aiTextureType::aiTextureType_LIGHTMAP);
			auto tCount10 = _material->GetTextureCount(aiTextureType::aiTextureType_REFLECTION);
		}

		pMeshObject->setVertexLayout(vertexLayout);
		pMeshObject->getVertexBuffer().initialize(_mesh->mNumVertices);
		pMeshObject->getIndexBuffer().setIndexSize(sizeof(UI32));

		UI64 vertexOffset = 0;
		UI64 dataSize = 0;

		for (UI32 _index = 0; _index < _mesh->mNumVertices; _index++)
		{
			for (auto attribute : vertexLayout.attributes)
			{
				dataSize = FormatSize(attribute.dataFormat) * attribute.dataCount;

				switch (attribute.attributeType)
				{
				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
					if (_mesh->HasPositions())
						pMeshObject->getVertexBuffer().addData(&_mesh->mVertices[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
					if (_mesh->HasNormals())
						pMeshObject->getVertexBuffer().addData(&_mesh->mNormals[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0:
					if (_mesh->HasVertexColors(0))
						pMeshObject->getVertexBuffer().addData(&_mesh->mColors[0][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_1:
					if (_mesh->HasVertexColors(1))
						pMeshObject->getVertexBuffer().addData(&_mesh->mColors[1][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_2:
					if (_mesh->HasVertexColors(2))
						pMeshObject->getVertexBuffer().addData(&_mesh->mColors[2][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_3:
					if (_mesh->HasVertexColors(3))
						pMeshObject->getVertexBuffer().addData(&_mesh->mColors[3][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0:
					if (_mesh->HasTextureCoords(0))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[0][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_1:
					if (_mesh->HasTextureCoords(1))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[1][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_2:
					if (_mesh->HasTextureCoords(2))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[2][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_3:
					if (_mesh->HasTextureCoords(3))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[3][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_4:
					if (_mesh->HasTextureCoords(4))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[4][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_5:
					if (_mesh->HasTextureCoords(5))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[5][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_6:
					if (_mesh->HasTextureCoords(6))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[6][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_7:
					if (_mesh->HasTextureCoords(7))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[7][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TANGENT:
					if (_mesh->HasTangentsAndBitangents())
						pMeshObject->getVertexBuffer().addData(&_mesh->mTangents[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BITANGENT:
					if (_mesh->HasTangentsAndBitangents())
						pMeshObject->getVertexBuffer().addData(&_mesh->mBitangents[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
					if (_mesh->HasTextureCoords(0))
						pMeshObject->getVertexBuffer().addData(&_mesh->mTextureCoords[0][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
					else
						pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY:
					/* TODO */
					pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID:
					/* TODO */
					pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT:
					/* TODO */
					pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				case Dynamik::DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
					/* TODO */
					pMeshObject->getVertexBuffer().setNull(dataSize, vertexOffset);
					break;

				default:
					DMK_ERROR_BOX("Invalid vertex attribute!");
					break;
				}

				vertexOffset += dataSize;
			}
		}

		aiFace face = {};
		for (UI32 index = 0; index < _mesh->mNumFaces; index++)
		{
			face = _mesh->mFaces[index];
			for (UI32 itr = 0; itr < face.mNumIndices; itr++)
				pMeshObject->getIndexBuffer().add(face.mIndices[itr]);
		}

#ifdef DMK_DEBUG
		DMK_INFO("Vertex count: " + std::to_string(pMeshObject->getVertexBuffer().size()));
		DMK_INFO("Index count: " + std::to_string(pMeshObject->getIndexBuffer().size()));

#endif // DMK_DEBUG
	}

	AssimpWrapper::AssimpWrapper()
	{
	}

	AssimpWrapper::~AssimpWrapper()
	{
	}

	DMKStaticMeshComponent AssimpWrapper::loadMeshComponent(VPTR pAiMeshObject, const DMKVertexLayout& vertexLayout)
	{
		DMKStaticMeshComponent _meshComponent;
		//meshLoadFunction(pAiMeshObject, vertexLayout, &_meshComponent);

		return _meshComponent;
	}

	DMK_FORCEINLINE void loadAllNodes(aiNode* pNode, DMKAnimNodeGraph* pGraph, UI64* pIndex, std::unordered_map<STRING, UI64>* pNodeMap, Matrix4F parentWorldTransform = Matrix4F(1.0))
	{
		UI64 myIndex = (*pIndex)++;
		(*pNodeMap).insert({ pNode->mName.data, myIndex });

		DMKAnimNode node((UI32)myIndex, pNode->mName.C_Str(), aiMatrixToMatrix4F(pNode->mTransformation));
		node.setWorldTransform(DMathLib::multiply(node.getNodeMatrix(), parentWorldTransform));
		pGraph->addNode(node);

		for (UI32 i = 0; i < pNode->mNumChildren; i++)
			pGraph->nodes[myIndex].addChildNodeIndex(*pIndex),
			loadAllNodes(pNode->mChildren[i], pGraph, pIndex, pNodeMap, node.getWorldTransform());
	}

	DMK_FORCEINLINE ARRAY<DMKAnimNodePose> loadPosees(aiNodeAnim* pNodeAnim, F32 numFramesToGenerate)
	{
		ARRAY<DMKAnimNodePose> container;

		for (UI64 index = 0; index <= Cast<UI64>(numFramesToGenerate); index++)
		{
			DMKAnimNodePose pose(index,
				Cast<F32>(pNodeAnim->mPositionKeys[index].mTime),
				aiVectorKeyToVector3F(pNodeAnim->mPositionKeys[index]),
				aiVectorKeyToVector3F(pNodeAnim->mScalingKeys[index]),
				aiQuatKeyToQuaternion(pNodeAnim->mRotationKeys[index]));

			container.pushBack(pose);
		}

		return container;
	}

	/* TODO */
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

	DMKAnimation AssimpWrapper::loadAnimation(VPTR pAiAnimation, VPTR pAiRootNode)
	{
		if (!pAiAnimation)
			return DMKAnimation();

		auto pAnimation = Cast<aiAnimation*>(pAiAnimation);

		DMKAnimation animation;
		animation.duration = Cast<F32>(pAnimation->mDuration);
		F32 numFramesToGenerate = std::ceilf(animation.duration * animation.framesPerSecond);

		/* Load pose containers */
		for (UI32 index = 0; index < pAnimation->mNumChannels; index++)
			animation.nodePoseMap[pAnimation->mChannels[index]->mNodeName.C_Str()] = loadPosees(pAnimation->mChannels[index], numFramesToGenerate);

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
				animMeshComponent.nodeGraph.nodes[animMeshComponent.nodeMap[pBone->mName.C_Str()]].setOffsetMatrix(aiMatrixToMatrix4F(pBone->mOffsetMatrix));

				for (UI32 i = 0; i < nodesPerVertex; i++)
				{
					animMeshComponent.nodeGraph.nodes[animMeshComponent.nodeMap[pBone->mName.data]].addVertexData(
						vertexOffset + Cast<UI64>(pBone->mWeights[i].mVertexId), pBone->mWeights[i].mWeight);

					//UI64 vertexID = vertexOffset + pBone->mWeights[i].mVertexId;
					//animMeshComponent.skinnedMesh.vertexBuffer.updateVertexAttribute(vertexID, nullptr, DMKVertexAttributeType());
				}
			}

			vertexOffset += animMeshComponent.skinnedMesh.vertexBuffer.size();
		}

		/* Load and bake animations */
		for (UI32 index = 0; index < _scene->mNumAnimations; index++)
		{
			auto animation = loadAnimation(_scene->mAnimations[index], _scene->mRootNode);
			animation.bake(animMeshComponent.nodeGraph, animMeshComponent.nodeMap);

			animMeshComponent.animations.pushBack(animation);
		}

		return animMeshComponent;
	}

	DMKAnimatedMeshComponent AssimpWrapper::loadAnimatedModel(const STRING& file, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
	{
		Assimp::Importer localImporter;

		return loadAnimatedMeshComponent((VPTR)localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs), vertexLayout, nodesPerVertex);
	}

	ARRAY<DMKStaticMeshComponent> AssimpWrapper::loadStaticModel(const STRING& file, const DMKVertexLayout& vertexLayout)
	{
		Assimp::Importer localImporter;

		auto _scene = localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!_scene)
		{
			DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
			return ARRAY<DMKStaticMeshComponent>();
		}

		ARRAY<DMKStaticMeshComponent> myModel(_scene->mNumMeshes, DMKStaticMeshComponent());
		{
			ARRAY<std::future<void>, 1, DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL> threads;

			for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
			{

				//threads.pushBack(std::async(std::launch::async, meshLoadFunction, _scene->mMeshes[_itr], Cast<VPTR>(_scene), vertexLayout, Cast<DMKStaticMeshComponent*>(myModel.location(_itr))));
			}
		}

		return myModel;
	}
}