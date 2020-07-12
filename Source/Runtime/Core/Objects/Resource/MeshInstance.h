// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_INSTANCE_H
#define _DYNAMIK_MESH_INSTANCE_H

#include "Primitives.h"

namespace Dynamik
{
	/*
	 Mesh instance structure
	 This structure holds a single mesh in a given model.
	*/
	struct DMK_API SMeshInstance {
		SMeshInstance() {}
		~SMeshInstance() {}

		/* Vertex Buffer */
		DMKVertexBuffer vertexBuffer;

		/* Index Buffer */
		ARRAY<UI32> indexBuffer;	/* TODO */
	};
}

#endif // !_DYNAMIK_MESH_INSTANCE_H
