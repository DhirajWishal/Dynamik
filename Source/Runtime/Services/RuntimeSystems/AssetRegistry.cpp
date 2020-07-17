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

		instance.assetMap[TEXT("SHADER_PBR_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\vert.spv");
		instance.assetMap[TEXT("SHADER_PBR_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\PBR\\frag.spv");

		instance.assetMap[TEXT("SHADER_SKELETAL_ANIMATION_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkeletalAnimation\\vert.spv");
		instance.assetMap[TEXT("SHADER_SKELETAL_ANIMATION_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkeletalAnimation\\frag.spv");

		instance.assetMap[TEXT("SHADER_SKYBOX_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkyBox\\vert.spv");
		instance.assetMap[TEXT("SHADER_SKYBOX_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\SkyBox\\frag.spv");
	
		instance.assetMap[TEXT("SHADER_BOUNDING_BOX_VERT_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\BoundingBox\\vert.spv");
		instance.assetMap[TEXT("SHADER_BOUNDING_BOX_FRAG_SPV")] = instance.defaultAssetBasePath + TEXT("\\Shaders\\BoundingBox\\frag.spv");

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
		return instance.assetMap[assetName];
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