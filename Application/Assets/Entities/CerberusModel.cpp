// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "CerberusModel.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Utilities/ShaderFactory.h"
#include "Core/Utilities/TextureFactory.h"

void CerberusModel::setCameraModule(DMKCameraModule* pCameraModule)
{
	this->pCameraModule = pCameraModule;
}

void CerberusModel::onInitializeStaticEntity()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	attribute.dataCount = 1;

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	layout.attributes.pushBack(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL;
	layout.attributes.pushBack(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RG_32_SF32;
	layout.attributes.pushBack(attribute);

	setMeshObjects(DMKMeshFactory::loadMeshes(TEXT("E:\\Dynamik\\Game Repository\\assets\\Cerberus\\Assets\\cerberus.fbx"), layout));

	/* Setup shader modules */
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_TBL_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_TBL_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

	/* Set resource requests. */
	setResourceRequests({ DMKResourceRequest::DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE, DMKResourceRequest::DMK_RESOURCE_REQUEST_BRDF_TABLE, DMKResourceRequest::DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE });

	/* Initialize the loaded shaders */
	for (UI64 index = 0; index < getMeshObjects()->size(); index++)
	{
		auto pStaticMesh = getMeshObject(index);

		pStaticMesh->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, TEXT("E:\\Dynamik\\Game Repository\\assets\\Cerberus\\Assets\\albedo.ktx")), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		pStaticMesh->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, TEXT("E:\\Dynamik\\Game Repository\\assets\\Cerberus\\Assets\\normal.ktx")), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		pStaticMesh->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, TEXT("E:\\Dynamik\\Game Repository\\assets\\Cerberus\\Assets\\ao.ktx")), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		pStaticMesh->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, TEXT("E:\\Dynamik\\Game Repository\\assets\\Cerberus\\Assets\\metallic.ktx")), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		pStaticMesh->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, TEXT("E:\\Dynamik\\Game Repository\\assets\\Cerberus\\Assets\\roughness.ktx")), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
	}

	dataVS.model = DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(90.0f), Vector3F(0.0f, 1.0f, 1.0f));

	const F32 p = 15.0f;
	camParamFS.light1 = Vector4F(-p, -p * 0.5f, -p, 1.0f);
	camParamFS.light2 = Vector4F(-p, -p * 0.5f, p, 1.0f);
	camParamFS.light3 = Vector4F(p, -p * 0.5f, p, 1.0f);
	camParamFS.light4 = Vector4F(p, -p * 0.5f, -p, 1.0f);
}

void CerberusModel::onUpdateStaticEntity()
{
	dataVS.projection = pCameraModule->matrix.projection;
	dataVS.view = pCameraModule->matrix.view;
	dataVS.camPos = pCameraModule->position * (-1.0f);

	/* To vertex shader */
	getShaderModule(0)->getUniform(0).setData(&dataVS);

	/* To fragment shader */
	getShaderModule(1)->getUniform(0).setData(&dataVS);
	getShaderModule(1)->getUniform(1).setData(&camParamFS);
}
