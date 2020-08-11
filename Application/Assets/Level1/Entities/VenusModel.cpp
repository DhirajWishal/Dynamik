// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "GameLibrary/GameModule.h"
#include "Core/Math/MathFunctions.h"
#include "VenusModel.h"

void VenusModel::initialize()
{
	auto vLayout = DMKVertexLayout::createBasicIBL();
	addComponents<DMKStaticMeshComponent>(DMKMeshFactory::loadMeshes(TEXT("E:\\Dynamik\\Game Repository\\assets\\venus.fbx"), vLayout));

	/* Setup shader modules */
	auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBuffer ubo1(0);
	ubo1.addAttribute(TEXT("projection"), sizeof(Matrix4F));
	ubo1.addAttribute(TEXT("model"), sizeof(Matrix4F));
	ubo1.addAttribute(TEXT("view"), sizeof(Matrix4F));
	ubo1.addAttribute(TEXT("camPos"), sizeof(Vector3F));
	ubo1.initialize();
	shaderVS.addUniform(ubo1);
	shaderVS.setInputAttributes(vLayout.getInputAttributes());

	auto shaderFS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBuffer ubo2(1);
	ubo2.addAttribute(TEXT("projection"), sizeof(Matrix4F));
	ubo2.addAttribute(TEXT("model"), sizeof(Matrix4F));
	ubo2.addAttribute(TEXT("view"), sizeof(Matrix4F));
	ubo2.addAttribute(TEXT("camPos"), sizeof(Vector3F));
	ubo2.initialize();
	shaderFS.addUniform(ubo2);

	DMKUniformBuffer ubo3(2);
	ubo3.addAttribute(TEXT("lights"), sizeof(Vector4F) * 4);
	ubo3.addAttribute(TEXT("exposure"), sizeof(F32));
	ubo3.addAttribute(TEXT("gamma"), sizeof(F32));
	ubo3.initialize();
	shaderFS.addUniform(ubo3);

	ARRAY<DMKResourceRequest> requests = { DMKResourceRequest::DMK_RESOURCE_REQUEST_BRDF_TABLE, DMKResourceRequest::DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE, DMKResourceRequest::DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE };

	/* Initialize the loaded shaders */
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);
		pStaticMesh->setResourceRequests(requests);

		pStaticMesh->addShaderModule(shaderVS);
		pStaticMesh->addShaderModule(shaderFS);
		pStaticMesh->addMaterial(DMKMaterial::createMetalPlatinum());
	}

	dataVS.model = DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(1.0f, 0.0f, 0.0f));

	const F32 p = 15;
	camParamFS.lights[0] = Vector4F(-p, p * 0.5f, -p, 1.0f);
	camParamFS.lights[1] = Vector4F(-p, p * 0.5f, p, 1.0f);
	camParamFS.lights[2] = Vector4F(p, p * 0.5f, p, 1.0f);
	camParamFS.lights[3] = Vector4F(p, p * 0.5f, -p, 1.0f);
}

void VenusModel::onUpdate(F32 timeStep)
{
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

		dataVS.projection = pCurrentModule->getCameraModule()->matrix.projection;
		dataVS.view = pCurrentModule->getCameraModule()->matrix.view;
		dataVS.camPos = pCurrentModule->getCameraModule()->position;

		pStaticMesh->getUniform(0, 0).setData(&dataVS);

		pStaticMesh->getUniform(1, 0).setData(&dataVS);
		pStaticMesh->getUniform(1, 1).setData(&camParamFS);
	}
}
