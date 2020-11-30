// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ShaderTools/ReflectionDigest.h"

namespace DMK
{
	namespace ShaderTools
	{
		/**
		 * SPIR-V Reflection object.
		 * This object is used to perform reflection on SPIR-V shader code.
		 */
		class SPIRVReflection {
		public:
			/**
			 * Default constructor.
			 */
			SPIRVReflection() {}

			/**
			 * Default destructor.
			 */
			~SPIRVReflection() {}

			/**
			 * Perform reflection on the shader code.
			 * Make sure that the shader code type is SPIR-V.
			 *
			 * @param mShaderCode: The shader code to perform reflection.
			 * @return ReflectionDigest object.
			 */
			ReflectionDigest Reflect(const GraphicsCore::ShaderCode& mShaderCode);
		};
	}
}