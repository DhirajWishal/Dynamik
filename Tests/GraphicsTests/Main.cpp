// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0
#include "Graphics/Engine.h"
using namespace DMK::GraphicsCore;

int main()
{
	Engine mGraphicsEngine = {};
	mGraphicsEngine.Initialize(GraphicsEngineCreateInfo());
	mGraphicsEngine.InitializeBackend();

	size_t counter = std::numeric_limits<size_t>::max();
	while (counter--);

	mGraphicsEngine.Terminate();

	return 0;
}