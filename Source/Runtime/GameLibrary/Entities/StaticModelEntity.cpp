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

	/* Initialize Uniform Buffers */
	DMKUniformBuffer uniformBuffer(0);
	uniformBuffer.addAttribute(TEXT("Model"), sizeof(Matrix4F));
	uniformBuffer.addAttribute(TEXT("View"), sizeof(Matrix4F));
	uniformBuffer.addAttribute(TEXT("Projection"), sizeof(Matrix4F));

	uniformBuffer.initialize();

	/* Upload Uniform to shaders */
	getShaderModule(0)->addUniform(uniformBuffer);

	/* Set shader input attributes */
	getShaderModule(0)->setInputAttributes(DMKVertexLayout::createBasic().getInputAttributes());
}

void DMKStaticModelEntity::onUpdateStaticEntity()
{
	Matrix4F model = Matrix4F::Identity;
	getShaderModule(0)->getUniform(0).setData(TEXT("Model"), &model);
	getShaderModule(0)->getUniform(0).setData(TEXT("View"), &_pCameraModule->matrix.view);
	getShaderModule(0)->getUniform(0).setData(TEXT("Projection"), &_pCameraModule->matrix.projection);
}

void DMKStaticModelEntity::onTerminateStaticEntity()
{
}

void DMKStaticModelEntity::addMeshObject(const DMKMeshObject& meshObject)
{
	meshObjects.pushBack(meshObject);
}

void DMKStaticModelEntity::setMeshObjects(ARRAY<DMKMeshObject> meshObjects)
{
	this->meshObjects = std::move(meshObjects);
}

DMKMeshObject* DMKStaticModelEntity::getMeshObject(I64 index)
{
	return getMeshObjects()->location(index);
}

ARRAY<DMKMeshObject>* DMKStaticModelEntity::getMeshObjects()
{
	return &meshObjects;
}

void DMKStaticModelEntity::addShaderModule(const DMKShaderModule& sModule)
{
	shaders.pushBack(sModule);
}

void DMKStaticModelEntity::setShaderModules(ARRAY<DMKShaderModule> sModules)
{
	shaders = std::move(sModules);
}

DMKShaderModule* DMKStaticModelEntity::getShaderModule(I32 index)
{
	return Cast<DMKShaderModule*>(shaders.location(index));
}

ARRAY<DMKShaderModule> DMKStaticModelEntity::getShaders()
{
	return shaders;
}

void DMKStaticModelEntity::addResourceRequest(const DMKResourceRequest& request)
{
	resourceRequests.pushBack(request);
}

void DMKStaticModelEntity::setResourceRequests(ARRAY<DMKResourceRequest> requests)
{
	resourceRequests = std::move(requests);
}

DMKResourceRequest DMKStaticModelEntity::getResourceRequest(I64 index)
{
	return resourceRequests[index];
}

ARRAY<DMKResourceRequest> DMKStaticModelEntity::getResourceRequests() const
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
