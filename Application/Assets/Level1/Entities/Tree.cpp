// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "GameLibrary/LevelComponent.h"
#include "Core/Math/MathFunctions.h"
#include "Tree.h"

void Tree::initialize()
{
	auto vLayout = DMKVertexLayout::createBasic();
	addComponents<DMKStaticMeshComponent>(DMKMeshFactory::loadMeshes("E:\\Dynamik\\Game Repository\\assets\\assets\\tree\\Tree.obj", vLayout));

	DMKUniformBufferObject uniform(0);
	uniform.addAttribute("Model", sizeof(Matrix4F));
	uniform.addAttribute("View", sizeof(Matrix4F));
	uniform.addAttribute("Proj", sizeof(Matrix4F));
	uniform.initialize();

	auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset("SHADER_3D_VERT_SPV"), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	shaderVS.addUniform(uniform);
	shaderVS.setInputAttributes(vLayout.getInputAttributes());

	auto shaderFS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset("SHADER_3D_FRAG_SPV"), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);

	ARRAY<STRING> textures;
	textures.pushBack("E:\\Dynamik\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg");
	textures.pushBack("E:\\Dynamik\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg");
	textures.pushBack("E:\\Dynamik\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg");
	textures.pushBack("E:\\Dynamik\\Game Repository\\assets\\assets\\tree\\bark_tree.jpg");
	textures.pushBack("E:\\Dynamik\\Game Repository\\assets\\assets\\tree\\ground.jpg");

	/* Initialize the loaded shaders */
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

		pStaticMesh->addShaderModule(shaderVS);
		pStaticMesh->addShaderModule(shaderFS);
		pStaticMesh->addTexture(textures[index], DMKTextureType::TEXTURE_TYPE_2D);
	}
}

void Tree::onUpdate(F32 timeStep)
{
	for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
	{
		auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

		uniformMVP.View = pCurrentLevel->getCameraModule()->matrix.view;
		uniformMVP.Projection = pCurrentLevel->getCameraModule()->matrix.projection;

		pStaticMesh->getUniform(0, 0).setData(&uniformMVP);
	}
}
