// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/ErrorHandler/Logger.h"
#include "Core/Maths/Vector/Vector3.h"
#include "Core/Memory/StaticAllocator.h"

int main()
{
	DMK::Logger::LogInfo(TEXT("Dynamik Core Test!"));

	DMK::Vector3 vector = { 0.0f, 2.0f, 1.0f };
	auto v2 = vector + vector;

	auto pData = DMK::StaticAllocator<int>::Allocate();
	DMK::StaticAllocator<int>::Deallocate(pData);
}