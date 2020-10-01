// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "OceanEnv.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Core/FileSystem/FileSystem.h"
#include "Core/Utilities/TextureFactory.h"
#include "Core/Utilities/ShaderFactory.h"
#include "Core/Objects/Resources/UniformBuffer.h"
#include "Services/RuntimeSystems/AssetRegistry.h" 

void OceanEnv::setCameraModule(DMKCameraModule* pCameraModule)
{
	this->pCameraModule = pCameraModule;
}

void OceanEnv::onInitializeEnvironment()
{
	std::vector<STRING> skyboxTexturePaths;
	skyboxTexturePaths.push_back("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\skybox\\right.jpg");
	skyboxTexturePaths.push_back("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\skybox\\left.jpg");
	skyboxTexturePaths.push_back("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\skybox\\top.jpg");
	skyboxTexturePaths.push_back("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\skybox\\bottom.jpg");
	skyboxTexturePaths.push_back("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\skybox\\front.jpg");
	skyboxTexturePaths.push_back("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\skybox\\back.jpg");

	skyBoxMesh = DMKMeshFactory::loadFromFile(DMKAssetRegistry::getAsset(TEXT("MODEL_SKYBOX_OBJ")), DMKVertexLayout::createBasicIBL());
	skyBoxMesh.getMaterial().addTexture(DMKTextureFactory::createCubeMap(skyboxTexturePaths), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);

	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_SKYBOX_CINEMATIC_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_SKYBOX_CINEMATIC_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
}

void OceanEnv::onUpdateEnvironment()
{
	Matrix4F mat = Matrix4F::Identity;
	
	getShaderModule(0)->getUniform(0).setData(TEXT("model"), &mat);
	getShaderModule(0)->getUniform(0).setData(TEXT("view"), &pCameraModule->matrix.view);
	getShaderModule(0)->getUniform(0).setData(TEXT("projection"), &pCameraModule->matrix.projection);
	getShaderModule(1)->getUniform(0).setData(&fsUBO);
}
