// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHCIS_CORE_SHADER_H
#define _DYNAMIK_GRAPHCIS_CORE_SHADER_H

#include "GraphicsCore/Backend/Common/GObject.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Shader location enum.
		 */
		enum class ShaderLocation {
			SHADER_LOCATION_VERTEX,
			SHADER_LOCATION_TESSELLATION,
			SHADER_LOCATION_GEOMETRY,
			SHADER_LOCATION_FRAGMENT,

			SHADER_LOCATION_COMPUTE,
		};

		/**
		 * Shader for Dynamik.
		 * This is the base class for all the shaders used by the engine.
		 */
		class Shader : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			Shader() {}

			/**
			 * Default destructor.
			 */
			virtual ~Shader() {}

			/**
			 * Perform reflection on the shader code.
			 */
			virtual void Reflect() {}

			/**
			 * Set the shader location.
			 *
			 * @param location: The location to be set.
			 */
			void SetLocation(ShaderLocation location) { this->location = location; }

			/**
			 * Get the shader location in the pipeline.
			 *
			 * @return: DMK::GraphcisCore::ShaderLocation enum.
			 */
			ShaderLocation GetLocation() const { return location; }

		protected:
			ShaderLocation location = ShaderLocation::SHADER_LOCATION_VERTEX;	// The location of the shader in the pipeline.
		};
	}
}

#endif // !_DYNAMIK_GRAPHCIS_CORE_SHADER_H
