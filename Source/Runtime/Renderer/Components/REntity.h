// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_ENTITY_H
#define _DYNAMIK_RENDERER_ENTITY_H

/*
 Author:	Dhiraj Wishal
 Date:		25/06/2020
*/
#include "RMeshObject.h"

namespace Dynamik
{
	/*
	 Renderer Entity
	*/
	class DMK_API REntity {
	public:
		REntity() = default;
		virtual ~REntity() = default;

		ARRAY<RMeshObject*> pMeshObjects;
	};
}

#endif // !_DYNAMIK_RENDERER_ENTITY_H
