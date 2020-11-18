// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Graphics/Engine.h"

#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void Engine::Initialize(const GraphicsEngineCreateInfo& initInfo)
		{
			// TODO
			pDevice = new VulkanBackend::VulkanDevice();
		}

		const GDevice* Engine::GetDevice() const
		{
			return pDevice;
		}

		void Engine::GraphicsThread(Thread::CommandHub* pCommandHub)
		{
			// Setup instance.
			Engine GraphicsEngine = {};
		}

		GDevice* Engine::GetDevice()
		{
			return pDevice;
		}
	}
}