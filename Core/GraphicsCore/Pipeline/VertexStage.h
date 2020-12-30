// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Vertex Stage of the graphics pipeline.
		 */
		class VertexStage {
		public:
			VertexStage() {}
			~VertexStage() {}

			void SetShaderCode(const ShaderCode& code) { mShaderCode = code; }
			void SetShaderCode(ShaderCode&& code) { mShaderCode = std::move(code); }
			ShaderCode& GetShaderCode() { return mShaderCode; }

		public:
			ShaderCode mShaderCode = {};
		};
	}
}