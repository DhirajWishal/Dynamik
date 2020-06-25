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

		static void setWorkingDirectory(const STRING& path);

	public:
		static DMKMeshComponent createBasicTriangle();

	private:
		STRING workingDirectory = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_MESH_FACTORY_H
