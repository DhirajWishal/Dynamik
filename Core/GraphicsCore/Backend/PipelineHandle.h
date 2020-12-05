// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"
#include "Core/Hash/Hasher.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Pipeline Type enum.
		 */
		enum class PipelineType : UI8 {
			UNDEFINED,		// Undefined pipeline.
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
			PipelineObjectHandle() {}
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

namespace std
{
	template<>
	struct hash<DMK::GraphicsCore::PipelineSpecification> {
		const size_t operator()(const DMK::GraphicsCore::PipelineSpecification& spec) const
		{
			size_t hash = 0;
			for (auto itr = spec.mShaders.begin(); itr != spec.mShaders.end(); itr++)
			{
				auto codeHash = itr->Hash();
				hash = DMK::Hasher::GetHash(&codeHash, sizeof(codeHash), hash);
			}

			UI64 type = static_cast<UI64>(spec.mType);
			return DMK::Hasher::GetHash(&type, sizeof(UI64), hash);
		}
	};
}