// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"

namespace DMK
{
	namespace ShaderTools
	{
		/**
		 * Reflection Digest object.
		 * Once a shader code is reflected, a reflection digest is created. This contains all the attributes and
		 * uniforms the shader code containes.
		 */
		class ReflectionDigest {
		public:
			/**
			 * Default constructor.
			 */
			ReflectionDigest() {}

			/**
			 * Copy constructor.
			 * 
			 * @param other: The other reflection digest.
			 */
			ReflectionDigest(const ReflectionDigest& other)
				: mUniforms(other.mUniforms), mInputAttributes(other.mInputAttributes), mOutputAttributes(other.mOutputAttributes) {}

			/**
			 * Default destructor.
			 */
			~ReflectionDigest() {}

			/**
			 * Get the uniforms in the digest.
			 *
			 * @return std::vector<GraphicsCore::Uniform> reference.
			 */
			std::vector<GraphicsCore::Uniform>& GetUniforms() { return mUniforms; }

			/**
			 * Get the input attributes in the digest.
			 *
			 * @return std::vector<GraphicsCore::ShaderAttribute> reference.
			 */
			std::vector<GraphicsCore::ShaderAttribute>& GetInputAttributes() { return mInputAttributes; }

			/**
			 * Get the output attributes in the digest.
			 *
			 * @return std::vector<GraphicsCore::ShaderAttribute> reference.
			 */
			std::vector<GraphicsCore::ShaderAttribute>& GetOutputAttributes() { return mOutputAttributes; }

			/**
			 * Move assignment operator.
			 *
			 * @param other: The other Reflection Digest object.
			 * @return The Reflection Digest (this) object refernece.
			 */
			ReflectionDigest& operator=(ReflectionDigest&& other) noexcept
			{
				this->mUniforms = std::move(other.mUniforms);
				this->mInputAttributes = std::move(other.mInputAttributes);
				this->mOutputAttributes = std::move(other.mOutputAttributes);

				return *this;
			}

		public:
			std::vector<GraphicsCore::Uniform> mUniforms;	// All the uniforms the shader had.
			std::vector<GraphicsCore::ShaderAttribute> mInputAttributes;	// All the input attributes.
			std::vector<GraphicsCore::ShaderAttribute> mOutputAttributes;	// All the output attributes.
		};
	}
}