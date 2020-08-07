// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "StaticEntity.h"

#include "../Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Types/StaticArray.h"
#include "../LevelComponent.h"
#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKStaticEntity::loadAsset(
		const STRING& asset,
		ARRAY<DMKTexture*> pTextures,
		const DMKVertexLayout& vLayout,
		ARRAY<DMKShaderModule> shaders)
	{
		addComponents<DMKStaticMeshComponent>(DMKMeshFactory::loadMeshes(asset, vLayout));

		isTexturesAvailable = pTextures.size();
		UI64 textureIndex = 0;

		for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
		{
			auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

			if (shaders.size())
			{
				for (auto shader : shaders)
					addShaderModule(shader);
			}
			else
			{
				if (isTexturesAvailable)
				{
					DMKUniformBuffer uniformVS(0);
					uniformVS.addAttribute("Model", sizeof(Matrix4F));
					uniformVS.addAttribute("View", sizeof(Matrix4F));
					uniformVS.addAttribute("Projection", sizeof(Matrix4F));
					uniformVS.initialize();

					auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_3D_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
					shaderVS.setInputAttributes(vLayout.getInputAttributes());
					shaderVS.addUniform(uniformVS);

					pStaticMesh->addShaderModule(shaderVS);
					pStaticMesh->addShaderModule(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_3D_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
				
					pStaticMesh->addTextureModule(pTextures[textureIndex]);
					textureIndex++;

					if (textureIndex >= pTextures.size())
						textureIndex = pTextures.size() - 1;
				}
				else
				{
					pStaticMesh->setResourceRequests({ DMKResourceRequest::DMK_RESOURCE_REQUEST_BRDF_TABLE, DMKResourceRequest::DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE, DMKResourceRequest::DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE });

					DMKUniformBuffer uniformVS(0);
					uniformVS.addAttribute(TEXT("projection"), sizeof(Matrix4F));
					uniformVS.addAttribute(TEXT("model"), sizeof(Matrix4F));
					uniformVS.addAttribute(TEXT("view"), sizeof(Matrix4F));
					uniformVS.addAttribute(TEXT("camPos"), sizeof(Vector3F));
					uniformVS.initialize();

					auto shaderVS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
					shaderVS.setInputAttributes(vLayout.getInputAttributes());
					shaderVS.addUniform(uniformVS);
					pStaticMesh->addShaderModule(shaderVS);

					DMKUniformBuffer uniformFS0(1);
					uniformFS0.addAttribute(TEXT("projection"), sizeof(Matrix4F));
					uniformFS0.addAttribute(TEXT("model"), sizeof(Matrix4F));
					uniformFS0.addAttribute(TEXT("view"), sizeof(Matrix4F));
					uniformFS0.addAttribute(TEXT("camPos"), sizeof(Vector3F));
					uniformFS0.initialize();

					DMKUniformBuffer uniformFS1(2);
					uniformFS1.addAttribute(TEXT("lights"), sizeof(Vector4F) * 4);
					uniformFS1.addAttribute(TEXT("exposure"), sizeof(F32));
					uniformFS1.addAttribute(TEXT("gamma"), sizeof(F32));
					uniformFS1.initialize();

					const F32 p = 15.0f;
					StaticArray<Vector4F, 4> lights;
					lights[0] = Vector4F(-p, p * 0.5f, -p, 1.0f);
					lights[1] = Vector4F(-p, p * 0.5f, p, 1.0f);
					lights[2] = Vector4F(p, p * 0.5f, p, 1.0f);
					lights[3] = Vector4F(p, p * 0.5f, -p, 1.0f);

					uniformFS1.setData("lights", lights.data());

					auto shaderFS = DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
					shaderFS.addUniform(uniformFS0);
					shaderFS.addUniform(uniformFS1);
					pStaticMesh->addShaderModule(shaderFS);

					pStaticMesh->addMaterial(DMKMaterial::createMetalGold());
				}
			}
		}
	}
	
	void DMKStaticEntity::onUpdate(F32 timeStep)
	{
		for (UI64 index = 0; index < getComponentArray<DMKStaticMeshComponent>()->size(); index++)
		{
			auto pStaticMesh = getComponent<DMKStaticMeshComponent>(index);

			if (isTexturesAvailable)
			{
				Matrix4F modelMat = DMathLib::translate(Matrix4F::Identity, Vector3F(3.0f, 0.0f, 0.0f));
				pStaticMesh->getUniform(0, 0).setData("Model", &modelMat);
				pStaticMesh->getUniform(0, 0).setData("View", &pCurrentLevel->getCameraModule()->matrix.view);
				pStaticMesh->getUniform(0, 0).setData("Projection", &pCurrentLevel->getCameraModule()->matrix.projection);
			}
		}
	}
}
