// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "CerberusModel.h"

#include "GameLibrary/LevelComponent.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "GameLibrary/LevelComponent.h"
#include "Core/Math/MathFunctions.h"
using namespace Dynamik;

void CerberusModel::initialize()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataCount = 1;

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
	layout.attributes.pushBack(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL;
	attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
	layout.attributes.pushBack(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES;
	attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC2;
	layout.attributes.pushBack(attribute);

	addComponents<DMKStaticMeshComponent>(DMKMeshFactory::loadMeshes(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\Cerberus\\Assets\\cerberus.fbx"), layout));

	/* Setup shader modules */
	auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_TBL_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBufferObject ubo1(0);
	ubo1.addAttribute(TEXT("projection"), sizeof(Matrix4F));
	ubo1.addAttribute(TEXT("model"), sizeof(Matrix4F));
	ubo1.addAttribute(TEXT("view"), sizeof(Matrix4F));
	ubo1.addAttribute(TEXT("camPos"), sizeof(Vector3F));
	ubo1.initialize();
	shaderVS.addUniform(ubo1);

	auto shaderFS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_TBL_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBufferObject ubo2(1);
	ubo2.addAttribute(TEXT("projection"), sizeof(Matrix4F));
	ubo2.addAttribute(TEXT("model"), sizeof(Matrix4F));
	ubo2.addAttribute(TEXT("view"), sizeof(Matrix4F));
	ubo2.addAttribute(TEXT("camPos"), sizeof(Vector3F));
	ubo2.initialize();
	shaderFS.addUniform(ubo2);

	DMKUniformBufferObject ubo3(2);
	ubo3.addAttribute(TEXT("lights"), sizeof(Vector4F) * 4);
	ubo3.addAttribute(TEXT("exposure"), sizeof(F32));
	ubo3.addAttribute(TEXT("gamma"), sizeof(F32));
	ubo3.initialize();
	shaderFS.addUniform(ubo3);

	ARRAY<DMKResourceRequest> requests = { DMKResourceRequest::DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE, DMKResourceRequest::DMK_RESOURCE_REQUEST_BRDF_TABLE, DMKResourceRequest::DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE };

	/* Initialize the loaded shaders */
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);
		pStaticMesh->setResourceRequests(requests);

		pStaticMesh->addShaderModule(shaderVS);
		pStaticMesh->addShaderModule(shaderFS);

		pStaticMesh->addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\Cerberus\\Assets\\albedo.ktx"), DMKTextureType::TEXTURE_TYPE_2D);
		pStaticMesh->addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\Cerberus\\Assets\\normal.ktx"), DMKTextureType::TEXTURE_TYPE_2D);
		pStaticMesh->addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\Cerberus\\Assets\\ao.ktx"), DMKTextureType::TEXTURE_TYPE_2D);
		pStaticMesh->addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\Cerberus\\Assets\\metallic.ktx"), DMKTextureType::TEXTURE_TYPE_2D);
		pStaticMesh->addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\Cerberus\\Assets\\roughness.ktx"), DMKTextureType::TEXTURE_TYPE_2D);
	}

	dataVS.model = DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(90.0f), Vector3F(0.0f, 1.0f, 1.0f));

	const F32 p = 15.0f;
	camParamFS.lights[0] = Vector4F(-p, -p * 0.5f, -p, 1.0f);
	camParamFS.lights[1] = Vector4F(-p, -p * 0.5f, p, 1.0f);
	camParamFS.lights[2] = Vector4F(p, -p * 0.5f, p, 1.0f);
	camParamFS.lights[3] = Vector4F(p, -p * 0.5f, -p, 1.0f);
}

void CerberusModel::onUpdate(F32 ts)
{
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

		dataVS.projection = pCurrentLevel->getCameraModule()->matrix.projection;
		dataVS.view = pCurrentLevel->getCameraModule()->matrix.view;
		dataVS.camPos = pCurrentLevel->getCameraModule()->position * (-1.0f);

		pStaticMesh->getUniform(0, 0).setData(&dataVS);

		pStaticMesh->getUniform(1, 0).setData(&dataVS);
		pStaticMesh->getUniform(1, 1).setData(&camParamFS);
	}
}
