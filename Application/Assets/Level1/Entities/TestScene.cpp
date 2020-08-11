// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "GameLibrary/GameModule.h"
#include "Core/Math/MathFunctions.h"

#include "Importer/Asset/ImageImporter.h"

#include "TestScene.h"

#include <functional>
#include <future>

void StaticLoad(DMKTexture** pTexture, STRING file)
{
	DMKImageImporter importer;
	*pTexture = importer.loadTexture2D(file);
}

void TestScene::initialize()
{
	auto vLayout = DMKVertexLayout::createBasic();
	addComponents<DMKStaticMeshComponent>(DMKMeshFactory::loadMeshes("E:\\Dynamik\\Game Repository\\assets\\assets\\postwar-city-exterior-scene\\source\\scene.fbx", vLayout));

	DMKUniformBuffer uniform(0);
	uniform.addAttribute("Model", sizeof(Matrix4F));
	uniform.addAttribute("View", sizeof(Matrix4F));
	uniform.addAttribute("Proj", sizeof(Matrix4F));
	uniform.initialize();

	auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset("SHADER_3D_VERT_SPV"), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	shaderVS.addUniform(uniform);
	shaderVS.setInputAttributes(vLayout.getInputAttributes());

	auto shaderFS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset("SHADER_3D_FRAG_SPV"), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);

	shaders.pushBack(shaderVS);
	shaders.pushBack(shaderFS);

	STRING basePath = "E:\\Dynamik\\Game Repository\\assets\\assets\\postwar-city-exterior-scene\\textures\\";

	ARRAY<STRING> textures;
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-gauche.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");
	textures.pushBack(basePath + "batiemts-principaux-droite.png");

	/* Initialize the loaded shaders */
	auto size = getComponentArray<DMKStaticMeshComponent>()->size();

	ARRAY<DMKTexture*> pTextures(size);

	{
		ARRAY<std::future<void>, 1, DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL> threads;
		
		for (UI32 itr = 0; itr < size; itr++)
			threads.pushBack(std::async(std::launch::async, StaticLoad, &pTextures[itr], textures[itr]));
	}

	for (UI64 index = 0; index < size; index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

		DMK_INFO("Mesh Name: " + pStaticMesh->name + " Mesh Index: " + std::to_string(index));

		pStaticMesh->addShaderModule(shaderVS);
		pStaticMesh->addShaderModule(shaderFS);
		pStaticMesh->addTextureModule(pTextures[index]);
	}
}

void TestScene::onUpdate(F32 timeStep)
{
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

		uniformMVP.Model = DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(1.0f, 0.0f, 0.0f));
		uniformMVP.View = pCurrentModule->getCameraModule()->matrix.view;
		uniformMVP.Projection = pCurrentModule->getCameraModule()->matrix.projection;

		pStaticMesh->getUniform(0, 0).setData(&uniformMVP);
	}
}
