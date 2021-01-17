// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace ShaderTools
	{
		namespace Utilities
		{
			/**
			 * Resolve padding in a shader code.
			 * Usually the shader code may contain some padding. SPIR-V Cross throws an error in the case of padding. To
			 * resolve this issue, the shader code must be padding-free.
			 *
			 * @param code: The shader code.
			 * @return The shader code without padding.
			 */
			std::vector<UI32> ResolvePadding(const std::vector<UI32>& code);
		}
	}
}