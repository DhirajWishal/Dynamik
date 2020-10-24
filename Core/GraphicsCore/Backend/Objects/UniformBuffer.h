// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHCIS_CORE_UNIFORM_BUFFER_H
#define _DYNAMIK_GRAPHCIS_CORE_UNIFORM_BUFFER_H

#include "Buffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Uniform Type enum.
		 */
		enum class UniformType : UI32 {
			UNIFORM_TYPE_UNIFORM_BUFFER,
		};

		/**
		 * Uniform Buffer for the Dynamik Engine.
		 * This object is used to submit uniform data to the shaders.
		 */
		class UniformBuffer : public Buffer {
		public:
			/**
			 * Default constructor.
			 */
			UniformBuffer() {}

			/**
			 * Default destructor.
			 */
			virtual ~UniformBuffer() {}

			/**
			 * Set the binding of the buffer in the shader.
			 *
			 * @param binding: The shader binding index.
			 */
			void SetBinding(UI32 binding) { this->binding = binding; }

			/**
			 * Get the shader binding index.
			 *
			 * @return: Unsigned 32 bit integer.
			 */
			UI32 GetBinding() const { return binding; }

			/**
			 * Set the type of the uniform buffer.
			 *
			 * @param type: The type to be set.
			 */
			void SetType(UniformType type) { this->type = type; }

			/**
			 * Get the uniform buffer type.
			 * 
			 * @return: DMK::GraphcisCore::UniformType enum.
			 */
			UniformType GetType() const { return type; }

		protected:
			UI32 binding = 0;	// Binding of the buffer.
			UniformType type = UniformType::UNIFORM_TYPE_UNIFORM_BUFFER;	// The uniform buffer type.
		};
	}
}

#endif // !_DYNAMIK_GRAPHCIS_CORE_UNIFORM_BUFFER_H
