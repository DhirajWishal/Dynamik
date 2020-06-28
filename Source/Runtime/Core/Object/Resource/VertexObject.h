// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VERTEX_OBJECT_H
#define _DYNAMIK_VERTEX_OBJECT_H

/*
 Author:	Dhiraj Wishal
 Date:		24/06/2020
*/
#include "Core/Macros/Global.h"

namespace Dynamik
{
	/*
	 Dynamik Vertex Object
	 This object is used to store all the necessary data of a single vertex of a given mesh.
	*/
	struct DMK_API DMKVertexObject {
		DMKVertexObject() = default;
		virtual ~DMKVertexObject() = default;
	};

	/*
	 Dynamik Vertex Buffer (Simple)
	 A simple vertex buffer to store basic vertex information.
	*/
	struct DMK_API DMKVertexBuffer_Simple : public DMKVertexObject {
		Vector3F position = Vector3F(0.0f);
		Vector3F color = Vector3F(0.0f);
	};
}

#endif // !_DYNAMIK_VERTEX_OBJECT_H
