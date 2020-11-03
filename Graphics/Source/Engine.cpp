// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Graphics/Engine.h"

#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace Graphics
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

		GDevice* Engine::GetDevice()
		{
			return pDevice;
		}
	}
}