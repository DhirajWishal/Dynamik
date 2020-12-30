// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Raster Graphics Pipeline Specification object.
		 * This object describes how the raster graphics pipeline should be made.
		 */
		class RasterGraphicsPipelineSpecification {
		public:
			/**
			 * Default constructor.
			 */
			RasterGraphicsPipelineSpecification() {}

			/**
			 * Default destructor.
			 */
			~RasterGraphicsPipelineSpecification() {}

			/**
			 * Get the hash of the specification.
			 *
			 * @return UI64 integer.
			 */
			UI64 Hash() const;

			std::vector<ShaderCode> mShaders;	// The shaders which the pipeline uses.
		};
	}
}