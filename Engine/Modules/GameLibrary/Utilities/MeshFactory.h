// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_FACTORY_H
#define _DYNAMIK_MESH_FACTORY_H

#include "GameLibrary/Entities/AnimatedModelEntity.h"

/*
 Dynamik Mesh Factory
*/
class DMK_API DMKMeshFactory {
	DMKMeshFactory() = default;
	~DMKMeshFactory() = default;

	static DMKMeshFactory instance;

public:
	DMKMeshFactory(const DMKMeshFactory&) = delete;
	DMKMeshFactory(DMKMeshFactory&&) = delete;
	DMKMeshFactory& operator=(const DMKMeshFactory&) = delete;
	DMKMeshFactory& operator=(DMKMeshFactory&&) = delete;

	/*
	 Internally used by the engine.
	*/
	static void setWorkingDirectory(const STRING& path);

public:
	/*
	 Create a basic triangle object.
	*/
	static DMKMeshObject createBasicTriangle();

	/*
	 Load mesh components from a file.
	*/
	static DMKMeshObject loadFromFile(const STRING& file, const DMKVertexLayout& vertexLayout = DMKVertexLayout::createBasic());

	/*
	 Create a default mesh component from a provided file.

	 @param path: Path to the file which contains the mesh data.
	*/
	static DMKMeshObject createDefault(const STRING& path);

	/*
	 Create a basic cube mesh.
	*/
	static DMKMeshObject createCube();

	/*
	 Create a basic sky box using texture files.

	 @param textureFiles: Texture files which are loaded to the sky box. These must be given as,
			+X, -X, +Y, -Y, +Z, -Z configuration.
			(eg: { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" })
	*/
	static DMKMeshObject createSkyBox(ARRAY<STRING> textureFiles);

	/*
	 Load an animated mesh from an asset file.

	 @param file: The asset file.
	*/
	static DMKMeshObject loadAnimatedMesh(const STRING& file);

	/*
	 Load a static model from an asset file.

	 @param file: The asset file.
	*/
	static DMKMeshObject loadStaticModel(const STRING& file, Vector3F position = { 0.0f, 0.0f, 0.0f }, Vector3F scale = { 1.0f, 1.0f, 1.0f });

	/*
	 Load all the meshes in a given asset.

	 @param asset: The asset path.
	*/
	static ARRAY<DMKMeshObject> loadMeshes(const STRING& file, DMKVertexLayout vertexLayout = DMKVertexLayout::createBasic());

private:
	STRING workingDirectory = TEXT("");
};

#endif // !_DYNAMIK_MESH_FACTORY_H
