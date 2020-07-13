// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_INSTANCE_H
#define _DYNAMIK_MESH_INSTANCE_H

#include "Primitives.h"
#include "Texture.h"

namespace Dynamik
{
	/*
	 Dynamik Mesh Instance Structure
	 This structure holds a single mesh in a given model.
	*/
	struct DMK_API DMKMeshInstance {
		DMKMeshInstance() {}
		~DMKMeshInstance() {}

		/* Vertex Buffer */
		DMKVertexBuffer vertexBuffer;

		/* Index Buffer */
		ARRAY<UI32> indexBuffer;	/* TODO */
	};
}

#endif // !_DYNAMIK_MESH_INSTANCE_H
