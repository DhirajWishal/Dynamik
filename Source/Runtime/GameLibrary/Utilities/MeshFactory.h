// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_FACTORY_H
#define _DYNAMIK_MESH_FACTORY_H

#include "Core/Components/RenderableComponents/StaticMeshComponent.h"

namespace Dynamik
{
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
		static DMKStaticMeshComponent createBasicTriangle();

		/*
		 Create a default mesh component from a provided file.

		 @param path: Path to the file which contains the mesh data.
		*/
		static DMKStaticMeshComponent createDefault(const STRING& path);

		/*
		 Create a basic cube mesh.
		*/
		static DMKStaticMeshComponent createCube();

		/*
		 Create a basic sky box using texture files.

		 @param textureFiles: Texture files which are loaded to the sky box. These must be given as,
				+X, -X, +Y, -Y, +Z, -Z configuration.
				(eg: { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" })
		*/
		static DMKStaticMeshComponent createSkyBox(ARRAY<STRING> textureFiles);

	private:
		STRING workingDirectory = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_MESH_FACTORY_H
