// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Hash/Hasher.h"

#include <xxhash.h>

namespace DMK
{
	namespace Hasher
	{
		UI64 GetHash(const void* pData, UI64 size, UI64 seed)
		{
			return XXH3_64bits(pData, size);
		}
	}
}