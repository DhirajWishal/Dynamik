// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Types/SparseSet.h"

#include <cstdlib>
#include <iostream>
#include <random>

int main()
{
	DMK::SparseSet<String> denseMap;

	auto a = denseMap.Insert("HelloWorld! 1");
	auto b = denseMap.Insert("HelloWorld! 2");
	auto c = denseMap.Insert("HelloWorld! 3");

	denseMap.Remove(b);

	denseMap.Clear();
}