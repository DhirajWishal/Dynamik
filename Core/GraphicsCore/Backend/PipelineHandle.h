// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Pipeline Type enum.
		 */
		enum class PipelineType : UI8 {
			UNDEFINED,
			GRAPHICS,		// Raster Graphics
			COMPUTE,		// Compute 
			RAY_TRACING,	// Ray Tracing (only if the device is supported).
		};

		/**
		 * Pipeline Specification structure.
		 * This structure defines how a pipeline should be initialized.
		 */
		struct PipelineSpecification {
			std::vector<ShaderCode> mShaders;	// Shaders of the pipeline.

			PipelineType mType = PipelineType::UNDEFINED;	// Pipeline type.
		};

		/**
		 * Pipeline Object Handle object.
		 * This object contains information about a single pipeline object.
		 */
		class PipelineObjectHandle {
		public:
			/**
			 * Default constructor.
			 */
			PipelineObjectHandle() {}

			/**
			 * Default destructor.
			 */
			~PipelineObjectHandle() {}

			PipelineSpecification mSpecification = {};	// Specification.
			UI64 mHandle = 0;	// The pipeline handle.
		};

		/**
		 * Pipeline Object Cache structure.
		 * This structure stores cache data which removes the need to process handle when retrieving pipeline data.
		 * Cache might not be valid if another pipeline is created or an existing pipeline was terminated.
		 */
		struct PipelineObjectCache {
			void* pCache = nullptr;	// The cache data pointer.	
			PipelineType mType = PipelineType::UNDEFINED;	// The pipeline type.
		};
	}
}