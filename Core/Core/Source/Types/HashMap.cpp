// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Maths/IncludeSIMD.h"
#include <vector>

namespace DMK
{
#if SSE_INSTR_SET > 7                  // AVX2 and later
#ifdef __GNUC__

#else

#endif // __GNUC__
#elif SSE_INSTR_SET == 7

#elif SSE_INSTR_SET == 6

#elif SSE_INSTR_SET == 5

#elif SSE_INSTR_SET == 4

#elif SSE_INSTR_SET == 3

#elif SSE_INSTR_SET == 2

#define CHUNK_SIZE  2

	long long FindIndex(std::vector<size_t>& hashVector, const size_t& hash)
	{
		{
			int mod = hashVector.size() % CHUNK_SIZE;
			if (mod)
				hashVector.insert(hashVector.end(), mod, 0);
		}

		int count = hashVector.size() / CHUNK_SIZE;
		__declspec(align(16)) unsigned __int64 hashBlock[CHUNK_SIZE] = { hash, hash };
		auto dataPtr = hashVector.data();

		size_t pos = 0;
		while (count--)
		{
			__declspec(align(16)) unsigned __int64 block[CHUNK_SIZE] = { *(dataPtr + pos + 0), *(dataPtr + pos + 1) };
			auto cmp = _mm_cmpeq_epi32(*reinterpret_cast<__m128i*>(hashBlock), *reinterpret_cast<__m128i*>(block));

			if (cmp.m128i_u64[pos + 0])
				return pos + 0;

			if (cmp.m128i_u64[pos + 1])
				return pos + 1;

			pos += CHUNK_SIZE;
		}

		return -1;
	}

#elif SSE_INSTR_SET == 1

#if SSE_INSTR_SET > 6

#endif
#if SSE_INSTR_SET > 0

#endif
#endif
}