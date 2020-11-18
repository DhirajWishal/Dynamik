// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Types/HashMap.h"

int main()
{
	DMK::HashMap<int, int> hash;
	for (int i = 0; i < 100; i++)
		hash[i] = i;

	for (int i = 0; i < 100; i++)
			printf("%d. %d\n", i, hash[i]);

	DMK::HashMap<int, int> h2;
	h2.Append(hash.Begin(), hash.End());
}