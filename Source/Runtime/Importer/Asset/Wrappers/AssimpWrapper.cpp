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
 @param pMeshObject: The mesh object pointer to load all the data to.
*/
DMK_FORCEINLINE void meshLoadFunction(VPTR pAiMeshObject, VPTR pAiScene, const DMKVertexLayout& vertexLayout, DMKMeshObject* pMeshObject)
{
	auto _mesh = Cast<aiMesh*>(pAiMeshObject);
	auto _scene = Cast<aiScene*>(pAiScene);
	pMeshObject->name = _mesh->mName.data;

	/* Resolve materials */
	aiString _texPath;
	aiMaterial* _material = nullptr;

	if (_scene)
	{
		if (_scene->HasMaterials())
		{
			_material = _scene->mMaterials[_mesh->mMaterialIndex];

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

			auto tCount11 = _material->GetTextureCount(aiTextureType::aiTextureType_BASE_COLOR);
			auto tCount12 = _material->GetTextureCount(aiTextureType::aiTextureType_NORMAL_CAMERA);
			auto tCount13 = _material->GetTextureCount(aiTextureType::aiTextureType_EMISSION_COLOR);
			auto tCount14 = _material->GetTextureCount(aiTextureType::aiTextureType_METALNESS);
			auto tCount15 = _material->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE_ROUGHNESS);
			auto tCount16 = _material->GetTextureCount(aiTextureType::aiTextureType_AMBIENT_OCCLUSION);
			auto tCount17 = _material->GetTextureCount(aiTextureType::aiTextureType_REFLECTION);
			auto tCount18 = _material->GetTextureCount(aiTextureType::aiTextureType_UNKNOWN);

			aiColor3D _diff;
			_material->Get(AI_MATKEY_COLOR_DIFFUSE, _diff);

			aiString _code;
			_material->Get(AI_MATKEY_NAME, _code);

			tCount0 = tCount0;

			_scene->mNumTextures;
		}
	}

	pMeshObject->vertexBuffer.initialize(_mesh->mNumVertices, vertexLayout);
	UI64 vertexOffset = 0;
	UI64 dataSize = 0;

	for (UI32 _index = 0; _index < _mesh->mNumVertices; _index++)
	{
		for (auto attribute : vertexLayout.attributes)
		{
			dataSize = FormatSize(attribute.dataFormat) * attribute.dataCount;

			switch (attribute.attributeType)
			{
			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION:
				if (_mesh->HasPositions())
					pMeshObject->vertexBuffer.addData(&_mesh->mVertices[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL:
				if (_mesh->HasNormals())
					pMeshObject->vertexBuffer.addData(&_mesh->mNormals[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0:
				if (_mesh->HasVertexColors(0))
					pMeshObject->vertexBuffer.addData(&_mesh->mColors[0][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_1:
				if (_mesh->HasVertexColors(1))
					pMeshObject->vertexBuffer.addData(&_mesh->mColors[1][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_2:
				if (_mesh->HasVertexColors(2))
					pMeshObject->vertexBuffer.addData(&_mesh->mColors[2][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_3:
				if (_mesh->HasVertexColors(3))
					pMeshObject->vertexBuffer.addData(&_mesh->mColors[3][_index], getCorrectSize<aiColor4D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0:
				if (_mesh->HasTextureCoords(0))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[0][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_1:
				if (_mesh->HasTextureCoords(1))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[1][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_2:
				if (_mesh->HasTextureCoords(2))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[2][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_3:
				if (_mesh->HasTextureCoords(3))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[3][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_4:
				if (_mesh->HasTextureCoords(4))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[4][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_5:
				if (_mesh->HasTextureCoords(5))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[5][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_6:
				if (_mesh->HasTextureCoords(6))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[6][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_7:
				if (_mesh->HasTextureCoords(7))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[7][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TANGENT:
				if (_mesh->HasTangentsAndBitangents())
					pMeshObject->vertexBuffer.addData(&_mesh->mTangents[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BITANGENT:
				if (_mesh->HasTangentsAndBitangents())
					pMeshObject->vertexBuffer.addData(&_mesh->mBitangents[_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES:
				if (_mesh->HasTextureCoords(0))
					pMeshObject->vertexBuffer.addData(&_mesh->mTextureCoords[0][_index], getCorrectSize<aiVector3D>(dataSize), vertexOffset);
				else
					pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY:
				/* TODO */
				pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID:
				/* TODO */
				pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT:
				/* TODO */
				pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			case DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM:
				/* TODO */
				pMeshObject->vertexBuffer.setNull(dataSize, vertexOffset);
				break;

			default:
				DMK_ERROR_BOX("Invalid vertex attribute!");
				break;
			}

			vertexOffset += dataSize;
		}
	}

	aiFace face;
	ARRAY<UI32> indexBuffer;
	for (UI32 index = 0; index < _mesh->mNumFaces; index++)
	{
		face = _mesh->mFaces[index];
		for (UI32 itr = 0; itr < face.mNumIndices; itr++)
			indexBuffer.pushBack(face.mIndices[itr]);
	}

	pMeshObject->indexBuffer.setIndexSize(sizeof(UI32));
	pMeshObject->indexBuffer.initialize(indexBuffer.size());
	pMeshObject->indexBuffer.set(indexBuffer.data(), indexBuffer.typeSize() * indexBuffer.size(), 0);

#ifdef DMK_DEBUG
	DMK_INFO("Vertex count: " + std::to_string(pMeshObject->vertexBuffer.size()));
	DMK_INFO("Index count: " + std::to_string(pMeshObject->indexBuffer.size()));

#endif // DMK_DEBUG
}

DMK_FORCEINLINE void loadAllNodes(aiNode* pNode, DMKAnimNodeGraph* pGraph, UI64* pIndex, std::unordered_map<STRING, UI64>* pNodeMap, Matrix4F parentWorldTransform = Matrix4F(1.0))
{
	UI64 myIndex = (*pIndex)++;
	pNodeMap->insert({ pNode->mName.data, myIndex });

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

AssimpWrapper::AssimpWrapper()
{
}

AssimpWrapper::~AssimpWrapper()
{
}

DMKStaticModelEntity AssimpWrapper::loadStaticModelEntity(const STRING& file, const DMKVertexLayout& vertexLayout)
{
	Assimp::Importer localImporter;

	auto _scene = localImporter.ReadFile(file, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenUVCoords);

	if (!_scene)
	{
		DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
		return DMKStaticModelEntity();
	}

	DMKStaticModelEntity model;
	model.meshObjects.resize(_scene->mNumMeshes, DMKMeshObject());
	{
		ARRAY<std::future<void>, 1, DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL> threads;

		for (UI32 _itr = 0; _itr < _scene->mNumMeshes; _itr++)
			threads.pushBack(std::async(std::launch::async, meshLoadFunction, _scene->mMeshes[_itr], Cast<VPTR>(_scene), vertexLayout, Cast<DMKMeshObject*>(model.meshObjects.location(_itr))));
	}

	return model;
}

DMKAnimatedModelEntity AssimpWrapper::loadAnimatedModelEntity(const STRING& file, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
{
	Assimp::Importer localImporter;

	return loadAnimatedModelEntity((VPTR)localImporter.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs), vertexLayout, nodesPerVertex);
}

DMKMeshObject AssimpWrapper::loadMeshObject(VPTR pAiMeshObject, const DMKVertexLayout& vertexLayout)
{
	DMKMeshObject meshObject = {};
	meshLoadFunction(pAiMeshObject, nullptr, vertexLayout, &meshObject);

	return meshObject;
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

DMKAnimatedModelEntity AssimpWrapper::loadAnimatedModelEntity(VPTR pAiSceneObject, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
{
	auto _scene = (aiScene*)pAiSceneObject;

	if (!_scene)
	{
		DMKErrorManager::issueErrorBox("Unable to load the mesh file!");
		return DMKAnimatedModelEntity();
	}

	return DMKAnimatedModelEntity();
}
