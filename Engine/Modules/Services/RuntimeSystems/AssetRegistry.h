// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ASSET_REGISTRY_H
#define _DYNAMIK_ASSET_REGISTRY_H

#include "Core/FileSystem/FileSystem.h"

/*
 Dynamik Asset Registry
 This singleton contains all the runtime assets of the engine. Clients are allowed to import and store
 their own assets to this.

 Default registry path is
	 $(SolutionDir)Source/Assets

 Asset naming convention:
   "TYPE_SUBTYPE_USAGE1_USAGE2_..._EXTENSION"
   eg:
	 "SHADER_3D_VERT_SPV"
*/
class DMKAssetRegistry {
	DMKAssetRegistry() {}
	~DMKAssetRegistry() {}

	static DMKAssetRegistry instance;
public:
	DMKAssetRegistry(const DMKAssetRegistry&) = delete;
	DMKAssetRegistry(DMKAssetRegistry&&) = delete;
	DMKAssetRegistry& operator=(const DMKAssetRegistry&) = delete;
	DMKAssetRegistry& operator=(DMKAssetRegistry&&) = delete;

	/*
	 This function is handled by the engine!
	 Set the base path of the engine asset files. These files are provided with the engine and are used
	 by the engine runtime.

	 @param path: Asset base path.
	*/
	static void setDefaultAssetBasePath(const STRING& path);

	/*
	 Get the default asset base path.
	*/
	static STRING getDefaultAssetBasePath();

	/*
	 Initialize the default assets.

	 @warn: This function must be called after setting the default asset base path.
	*/
	static void initializeDefaultAssets();

	/*
	 Get an asset by its name.

	 @param assetName: Name of the asset.
	*/
	static STRING getAsset(const STRING& assetName);

	/*
	 Add an asset to the registry.

	 @param assetName: Name of the asset.
	 @param assetPath: Path of the asset.
	*/
	static void addAsset(const STRING& assetName, const STRING& assetPath);

	/*
	 Get the number of registered assets in the registry.
	*/
	static UI64 getNumberOfRegisteredAssets();

	/*
	 Get all the registered asset names.
	*/
	static ARRAY<STRING> getAllRegisteredAssetNames();

	/*
	 Get the asset map of the registry.
	*/
	static std::unordered_map<STRING, STRING> getAssetMap();

private:
	std::unordered_map<STRING, STRING> assetMap;
	STRING defaultAssetBasePath = TEXT("");
};

#endif // !_DYNAMIK_ASSET_REGISTRY_H
