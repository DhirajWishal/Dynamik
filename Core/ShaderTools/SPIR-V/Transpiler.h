// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"

namespace DMK
{
	namespace ShaderTools
	{
		/**
		 * SPIR-V Transpiler object.
		 * This object transpiles SPIR-V code to GLSL and HLSL.
		 */
		class SPIRVTranspiler {
		public:
			/**
			 * Default constructor.
			 */
			SPIRVTranspiler() {}

			/**
			 * Default destructor.
			 */
			~SPIRVTranspiler() {}

			/**
			 * Initialize the transpiler with the shader code.
			 * Make sure that the shader code is SPIR-V.
			 * 
			 * @param pShaderCode: The pointer to the shader code.
			 */
			void Initialize(GraphicsCore::ShaderCode* pShaderCode);

			/**
			 * Transpile the shader code to GLSL.
			 * 
			 * @return ShaderCode object with the GLSL shader data.
			 */
			GraphicsCore::ShaderCode GetGLSL();

			/**
			 * Transpile the shader code to HLSL.
			 *
			 * @return ShaderCode object with the HLSL shader data.
			 */
			GraphicsCore::ShaderCode GetHLSL();

		private:
			GraphicsCore::ShaderCode* pShaderCode = nullptr;	// The shader code pointer.
		};
	}
}