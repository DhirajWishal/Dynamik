// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VenusModel.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Utilities/ShaderFactory.h"

void VenusModel::setCameraModule(DMKCameraModule* pCameraModule)
{
	this->pCameraModule = pCameraModule;
}

void VenusModel::onInitializeStaticEntity()
{
	auto vLayout = DMKVertexLayout::createBasicIBL();
	setMeshObjects(DMKMeshFactory::loadMeshes(TEXT("E:\\Dynamik\\Game Repository\\assets\\venus.fbx"), vLayout));

	/* Setup shader modules */
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

	/* Set resource requests */
	setResourceRequests({ DMKResourceRequest::DMK_RESOURCE_REQUEST_BRDF_TABLE, DMKResourceRequest::DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE, DMKResourceRequest::DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE });

	/* Setup mesh data */
	for (UI32 index = 0; index < getMeshObjects()->size(); index++)
		getMeshObject(index)->setMaterial(DMKMaterial::createMetalPlatinum());

	/* Initialize uniform data. */
	dataVS.model = DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(1.0f, 0.0f, 0.0f));

	const F32 p = 15;
	camParamFS.lights[0] = Vector4F(-p, p * 0.5f, -p, 1.0f);
	camParamFS.lights[1] = Vector4F(-p, p * 0.5f, p, 1.0f);
	camParamFS.lights[2] = Vector4F(p, p * 0.5f, p, 1.0f);
	camParamFS.lights[3] = Vector4F(p, p * 0.5f, -p, 1.0f);
}

void VenusModel::onUpdateStaticEntity()
{
	dataVS.projection = pCameraModule->matrix.projection;
	dataVS.view = pCameraModule->matrix.view;
	dataVS.camPos = pCameraModule->position;

	getShaderModule(0)->getUniform(0).setData(&dataVS);

	getShaderModule(1)->getUniform(0).setData(&dataVS);
	getShaderModule(1)->getUniform(0).setData(&camParamFS);
}
