// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "StaticModelEntity.h"

#include "../Camera/CameraModule.h"
#include "Core/Utilities/ShaderFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"

/* ---------- Global Helpers ---------- */
DMKCameraModule* _pCameraModule = nullptr;

/* ---------- Class Definitions ---------- */
void DMKStaticModelEntity::onInitializeStaticEntity()
{
	/* Initialize Shaders */
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_3D_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_3D_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
}

void DMKStaticModelEntity::onUpdateStaticEntity()
{
	Matrix4F model = Matrix4F::Identity;
	getShaderModule(0)->getUniform(0).setData(TEXT("model"), &model);
	getShaderModule(0)->getUniform(0).setData(TEXT("view"), &_pCameraModule->matrix.view);
	getShaderModule(0)->getUniform(0).setData(TEXT("proj"), &_pCameraModule->matrix.projection);
}

void DMKStaticModelEntity::onTerminateStaticEntity()
{
}

void DMKStaticModelEntity::addMeshObject(const DMKMeshObject& meshObject)
{
	meshObjects.push_back(meshObject);
}

void DMKStaticModelEntity::setMeshObjects(std::vector<DMKMeshObject> meshObjects)
{
	this->meshObjects = std::move(meshObjects);
}

DMKMeshObject* DMKStaticModelEntity::getMeshObject(I64 index)
{
	return &getMeshObjects()->at(index);
}

std::vector<DMKMeshObject>* DMKStaticModelEntity::getMeshObjects()
{
	return &meshObjects;
}

void DMKStaticModelEntity::addShaderModule(const DMKShaderModule& sModule)
{
	shaders.push_back(sModule);
}

void DMKStaticModelEntity::setShaderModules(std::vector<DMKShaderModule> sModules)
{
	shaders = std::move(sModules);
}

DMKShaderModule* DMKStaticModelEntity::getShaderModule(I32 index)
{
	return Cast<DMKShaderModule*>(&shaders.at(index));
}

std::vector<DMKShaderModule> DMKStaticModelEntity::getShaders()
{
	return shaders;
}

void DMKStaticModelEntity::addResourceRequest(const DMKResourceRequest& request)
{
	resourceRequests.push_back(request);
}

void DMKStaticModelEntity::setResourceRequests(std::vector<DMKResourceRequest> requests)
{
	resourceRequests = std::move(requests);
}

DMKResourceRequest DMKStaticModelEntity::getResourceRequest(I64 index)
{
	return resourceRequests[index];
}

std::vector<DMKResourceRequest> DMKStaticModelEntity::getResourceRequests() const
{
	return resourceRequests;
}

void DMKStaticModelEntity::clearStaticModel()
{
	for (auto mesh : meshObjects)
	{
		mesh.clearVertexAndIndexBuffers();

		for (UI32 index = 0; index < mesh.getMaterial().textureContainers.size(); index++)
		{
			mesh.getMaterial().textureContainers[index].pTexture->clear();
			StaticAllocator<DMKTexture>::deallocate(mesh.getMaterial().textureContainers[index].pTexture, 0);
		}

		mesh.getMaterial().textureContainers.clear();
	}

	meshObjects.clear();

	isInitializedStaticModel = false;
}

void _Helpers::_SetDefaultStaticModelCameraModule(DMKCameraModule* pCameraModule)
{
	_pCameraModule = pCameraModule;
}
