// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ShaderTools/SPIR-V/Utilities.h"
#include "Core/Memory/Functions.h"

namespace DMK
{
	namespace ShaderTools
	{
		namespace Utilities
		{
			std::vector<UI32> ResolvePadding(const std::vector<UI32>& code)
			{
				// Get the final code size.
				const UI64 mFinalCodeSize = code.size() / 4;

				// Resize the vector.
				std::vector<UI32> mCode(mFinalCodeSize);

				// Copy and return the copied vector.
				MemoryFunctions::CopyData(mCode.data(), code.data(), sizeof(UI32) * mFinalCodeSize);
				return mCode;
			}
		}
	}
}
