// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_FACTORY_H
#define _DYNAMIK_MESH_FACTORY_H

/*
 Author:	Dhiraj Wishal
 Date:		07/06/2020
*/
#include "ComponentSystem/Components/RenderableComponents/MeshComponent.h"

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
		static DMKMeshComponent createBasicTriangle();

		/*
		 Create a default mesh component from a provided file.

		 @param path: Path to the file which contains the mesh data.
		*/
		static DMKMeshComponent createDefault(const STRING& path);

	private:
		STRING workingDirectory = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_MESH_FACTORY_H
