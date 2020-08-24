// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AssetRegistry.h"

namespace Dynamik
{
	DMKAssetRegistry DMKAssetRegistry::instance;

	void DMKAssetRegistry::setDefaultAssetBasePath(const STRING& path)
	{
		instance.defaultAssetBasePath = path;
	}

	STRING DMKAssetRegistry::getDefaultAssetBasePath()
	{
		return instance.defaultAssetBasePath;
	}

	void DMKAssetRegistry::initializeDefaultAssets()
	{
		/* Initialize models */
		instance.assetMap[TEXT("MODEL_CUBE_OBJ")] = instance.defaultAssetBasePath + TEXT("\\Models\\Cube\\Cube.obj");
		instance.assetMap[TEXT("MODEL_SKYBOX_OBJ")] = instance.defaultAssetBasePath + TEXT("\\Models\\SkyBox\\SkySphere.obj");

		/* Initialize shaders */
		instance.assetMap[TEXT("SHADER_3D_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\3D\\vert.spv");
		instance.assetMap[TEXT("SHADER_3D_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\3D\\frag.spv");

		instance.assetMap[TEXT("SHADER_PBR_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\Tests\\vert.spv");
		instance.assetMap[TEXT("SHADER_PBR_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\Tests\\frag.spv");

		instance.assetMap[TEXT("SHADER_PBR_IBL_BRDF_TABLE_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\BRDFTable.vert");
		instance.assetMap[TEXT("SHADER_PBR_IBL_BRDF_TABLE_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\BRDFTable.frag");
		instance.assetMap[TEXT("SHADER_PBR_IBL_BRDF_TABLE_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\BRDFTable.vert.spv");
		instance.assetMap[TEXT("SHADER_PBR_IBL_BRDF_TABLE_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\BRDFTable.frag.spv");

		instance.assetMap[TEXT("SHADER_PBR_IBL_FILTER_CUBE_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\filterCube.vert");
		instance.assetMap[TEXT("SHADER_PBR_IBL_FILTER_CUBE_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\filterCube.vert.spv");

		instance.assetMap[TEXT("SHADER_PBR_IBL_PREFILTER_CUBE_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\prefilterCube.frag");
		instance.assetMap[TEXT("SHADER_PBR_IBL_PREFILTER_CUBE_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\prefilterCube.frag.spv");
		instance.assetMap[TEXT("SHADER_PBR_IBL_PREFILTER_ENVIRONMENT_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\prefilterEnvironment.frag");
		instance.assetMap[TEXT("SHADER_PBR_IBL_PREFILTER_ENVIRONMENT_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\prefilterEnvironment.frag.spv");
		instance.assetMap[TEXT("SHADER_PBR_IBL_IRRADIANCE_CUBE_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\irradianceCube.frag");
		instance.assetMap[TEXT("SHADER_PBR_IBL_IRRADIANCE_CUBE_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\irradianceCube.frag.spv");
		
		instance.assetMap[TEXT("SHADER_PBR_IBL_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\shader.vert");
		instance.assetMap[TEXT("SHADER_PBR_IBL_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\shader.frag");
		instance.assetMap[TEXT("SHADER_PBR_IBL_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\vert.spv");
		instance.assetMap[TEXT("SHADER_PBR_IBL_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\IBL\\frag.spv");

		instance.assetMap[TEXT("SHADER_PBR_TBL_BRDF_TABLE_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\BRDFTable.vert");
		instance.assetMap[TEXT("SHADER_PBR_TBL_BRDF_TABLE_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\BRDFTable.frag");
		instance.assetMap[TEXT("SHADER_PBR_TBL_FILTER_CUBE_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\filterCube.vert");
		instance.assetMap[TEXT("SHADER_PBR_TBL_PREFILTER_CUBE_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\prefilterCube.frag");
		instance.assetMap[TEXT("SHADER_PBR_TBL_PREFILTER_ENVIRONMENT_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\prefilterEnvironment.frag");
		instance.assetMap[TEXT("SHADER_PBR_TBL_IRRADIANCE_CUBE_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\irradianceCube.frag");
		instance.assetMap[TEXT("SHADER_PBR_TBL_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\shader.vert");
		instance.assetMap[TEXT("SHADER_PBR_TBL_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\shader.frag");
		instance.assetMap[TEXT("SHADER_PBR_TBL_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\vert.spv");
		instance.assetMap[TEXT("SHADER_PBR_TBL_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\TBL\\frag.spv");

		instance.assetMap[TEXT("SHADER_SKELETAL_ANIMATION_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkeletalAnimation\\vert.spv");
		instance.assetMap[TEXT("SHADER_SKELETAL_ANIMATION_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkeletalAnimation\\frag.spv");

		instance.assetMap[TEXT("SHADER_SKYBOX_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkyBox\\vert.spv");
		instance.assetMap[TEXT("SHADER_SKYBOX_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkyBox\\frag.spv");

		instance.assetMap[TEXT("SHADER_SKYBOX_CINEMATIC_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkyBox\\Cinematic\\vert.spv");
		instance.assetMap[TEXT("SHADER_SKYBOX_CINEMATIC_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkyBox\\Cinematic\\frag.spv");

		instance.assetMap[TEXT("SHADER_BOUNDING_BOX_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\BoundingBox\\vert.spv");
		instance.assetMap[TEXT("SHADER_BOUNDING_BOX_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\BoundingBox\\frag.spv");

		instance.assetMap[TEXT("SHADER_IM_GUI_UI_VERT")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\ImGui\\UI.vert");
		instance.assetMap[TEXT("SHADER_IM_GUI_UI_FRAG")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\ImGui\\UI.frag");

		/* Initialize textures */
		instance.assetMap[TEXT("TEXTURE_SKYBOX_BACK_JPG")] = instance.defaultAssetBasePath + TEXT("\\Textures\\SkyBox\\back.jpg");
		instance.assetMap[TEXT("TEXTURE_SKYBOX_BOTTOM_JPG")] = instance.defaultAssetBasePath + TEXT("\\Textures\\SkyBox\\bottom.jpg");
		instance.assetMap[TEXT("TEXTURE_SKYBOX_FRONT_JPG")] = instance.defaultAssetBasePath + TEXT("\\Textures\\SkyBox\\front.jpg");
		instance.assetMap[TEXT("TEXTURE_SKYBOX_LEFT_JPG")] = instance.defaultAssetBasePath + TEXT("\\Textures\\SkyBox\\left.jpg");
		instance.assetMap[TEXT("TEXTURE_SKYBOX_RIGHT_JPG")] = instance.defaultAssetBasePath + TEXT("\\Textures\\SkyBox\\right.jpg");
		instance.assetMap[TEXT("TEXTURE_SKYBOX_TOP_JPG")] = instance.defaultAssetBasePath + TEXT("\\Textures\\SkyBox\\top.jpg");
	}

	STRING DMKAssetRegistry::getAsset(const STRING& assetName)
	{
		if (instance.assetMap.find(assetName) != instance.assetMap.end())
			return instance.assetMap[assetName];

		DMK_ERROR("The requested asset is not available in the registry! The Asset: " + assetName);
		return STRING();
	}

	void DMKAssetRegistry::addAsset(const STRING& assetName, const STRING& assetPath)
	{
		instance.assetMap.insert({ assetName, assetPath });
	}

	UI64 DMKAssetRegistry::getNumberOfRegisteredAssets()
	{
		return instance.assetMap.size();
	}

	ARRAY<STRING> DMKAssetRegistry::getAllRegisteredAssetNames()
	{
		ARRAY<STRING> names;

		for (auto asset : instance.assetMap)
			names.pushBack(asset.first);

		return names;
	}

	std::unordered_map<STRING, STRING> DMKAssetRegistry::getAssetMap()
	{
		return instance.assetMap;
	}
}