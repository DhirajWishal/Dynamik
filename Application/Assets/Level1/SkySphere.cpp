// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "SkySphere.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Core/FileSystem/FileSystem.h"
#include "Core/Utilities/TextureFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "GameLibrary/GameModule.h"
using namespace Dynamik;

SkySphere::SkySphere()
{
	ARRAY<STRING> texturePaths;
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");

	auto vLayout = DMKVertexLayout::createBasicIBL();
	skyBox = DMKMeshFactory::loadFromFile(TEXT("E:\\Dynamik\\Game Repository\\assets\\assets\\Skybox\\SkySphere.obj"), vLayout);
	skyBox.addTextureModule(DMKTextureFactory::createCubeMap(texturePaths));

	auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_SKYBOX_CINEMATIC_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	DMKUniformBuffer unifomVS(0);
	unifomVS.addAttribute(TEXT("projection"), sizeof(Matrix4F));
	unifomVS.addAttribute(TEXT("view"), sizeof(Matrix4F));
	unifomVS.addAttribute(TEXT("model"), sizeof(Matrix4F));
	unifomVS.initialize();
	shaderVS.addUniform(unifomVS);
	shaderVS.setInputAttributes(vLayout.getInputAttributes());

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

void SkySphere::onUpdate(F32 timeStep)
{
	Matrix4F mat = Matrix4F::Identity;
	shaderModules[0].getUniform(0).setData(TEXT("projection"), &pCurrentModule->getCameraModule()->matrix.projection);
	shaderModules[0].getUniform(0).setData(TEXT("view"), &pCurrentModule->getCameraModule()->matrix.view);
	shaderModules[0].getUniform(0).setData(TEXT("model"), &mat);
	shaderModules[1].getUniform(0).setData(&fsUBO);
}
