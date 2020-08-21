// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "OceanEnv.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Core/FileSystem/FileSystem.h"
#include "Core/Utilities/TextureFactory.h"
#include "Core/Utilities/ShaderFactory.h"
#include "Core/Objects/Resources/UniformBuffer.h"
#include "Services/RuntimeSystems/AssetRegistry.h"

using namespace Dynamik;

void OceanEnv::setCameraModule(DMKCameraModule* pCameraModule)
{
	this->pCameraModule = pCameraModule;
}

void OceanEnv::onInitializeEnvironment()
{
	ARRAY<STRING> skyboxTexturePaths;
	skyboxTexturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	skyboxTexturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	skyboxTexturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	skyboxTexturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	skyboxTexturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	skyboxTexturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");

	skyBoxMesh = DMKMeshFactory::loadFromFile(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\Skybox\\SkySphere.obj"), DMKVertexLayout::createBasicIBL());
	skyBoxMesh.getMaterial().addTexture(DMKTextureFactory::createCubeMap(skyboxTexturePaths), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);

	auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_SKYBOX_CINEMATIC_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBuffer unifomVS(0);
	unifomVS.addAttribute(TEXT("projection"), sizeof(Matrix4F));
	unifomVS.addAttribute(TEXT("view"), sizeof(Matrix4F));
	unifomVS.addAttribute(TEXT("model"), sizeof(Matrix4F));
	unifomVS.initialize();
	shaderVS.addUniform(unifomVS);
	shaderVS.addInputAttribute(DMKShaderInputAttribute(DMKFormat::DMK_FORMAT_RGBA_32_SF32, 1));
	shaderVS.addInputAttribute(DMKShaderInputAttribute(DMKFormat::DMK_FORMAT_RGBA_32_SF32, 1));
	shaderVS.addInputAttribute(DMKShaderInputAttribute(DMKFormat::DMK_FORMAT_RG_32_SF32, 1));

	addShaderModule(shaderVS);

	auto shaderFS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_SKYBOX_CINEMATIC_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBuffer unifomFS(1);
	unifomFS.addAttribute(TEXT("lights"), sizeof(Vector4F) * 4);
	unifomFS.addAttribute(TEXT("exposure"), sizeof(F32));
	unifomFS.addAttribute(TEXT("gamma"), sizeof(F32));
	unifomFS.initialize();
	shaderFS.addUniform(unifomFS);
	addShaderModule(shaderFS);
}

void OceanEnv::onUpdateEnvironment()
{
	Matrix4F mat = Matrix4F::Identity;
	
	getShaderModule(0)->getUniform(0).setData(TEXT("projection"), &pCameraModule->matrix.projection);
	getShaderModule(0)->getUniform(0).setData(TEXT("view"), &pCameraModule->matrix.view);
	getShaderModule(0)->getUniform(0).setData(TEXT("model"), &mat);
	getShaderModule(1)->getUniform(0).setData(&fsUBO);
}
