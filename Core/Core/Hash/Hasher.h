// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Hasher
	{
		/**
		 * Generate hash using the data and the size of it.
		 * This method uses the xxhash library to generate the hash.
		 *
		 * @param pData: The data pointer.
		 * @param size: The size of the data block.
		 * @param seed: The seed to generate the hash from. Default is 0.
		 * @return The hash as UI64.
		 */
		UI64 GetHash(const void* pData, UI64 size, UI64 seed = 0);
	}
}