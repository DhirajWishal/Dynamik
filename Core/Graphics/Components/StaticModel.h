// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_STATIC_MODEL_H
#define _DYNAMIK_GRAPHICS_STATIC_MODEL_H

#include "GraphicsCore/Objects/StaticMeshObject.h"

#include <vector>

namespace DMK
{
	namespace Graphics
	{
		/**
		 * Static Model object.
		 * This object holds information about a single static model. These models does not contain any animation.
		 */
		class StaticModel {
		public:
			/**
			 * Default constructor.
			 */
			StaticModel() {}

			/**
			 * Default destructor.
			 */
			~StaticModel() {}

			std::vector<GraphicsCore::StaticMeshObject> mStaticMeshes;
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_STATIC_MODEL_H
