// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Graphics/Engine.h"
#include "Core/ErrorHandler/Logger.h"
#include "VulkanBackend/VulkanBackendFunction.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void Engine::Initialize(const GraphicsEngineCreateInfo& initInfo)
		{
			// Setup the backend thread.
			switch (initInfo.backendAPI)
			{
			case DMK::GraphicsCore::GraphicsBackendAPI::GRAPHICS_BACKEND_API_VULKAN:
				mBackendThread.swap(std::thread(VulkanBackend::VulkanBackendFunction, &mCommandQueue));
				break;
			case DMK::GraphicsCore::GraphicsBackendAPI::GRAPHICS_BACKEND_API_DIRECT_X:
				break;
			case DMK::GraphicsCore::GraphicsBackendAPI::GRAPHICS_BACKEND_API_WEB_GPU:
				break;
			default:
				Logger::LogError(TEXT("Invalid Graphics Backend API type!"));
				break;
			}
		}
	}
}