// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Graphics/Engine.h"
#include "Core/ErrorHandler/Logger.h"
#include "VulkanBackend/VulkanBackendFunction.h"

#include "GraphicsCore/Commands/CoreCommands.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void Engine::Initialize(const GraphicsEngineCreateInfo& initInfo)
		{
			// Setup the backend thread.
			switch (initInfo.backendAPI)
			{
			case DMK::GraphicsCore::GraphicsBackendAPI::VULKAN:
				mBackendThread.swap(std::thread(VulkanBackend::VulkanBackendFunction, &mCommandQueue));
				break;
			case DMK::GraphicsCore::GraphicsBackendAPI::DIRECT_X:
				break;
			case DMK::GraphicsCore::GraphicsBackendAPI::WEB_GPU:
				break;
			default:
				Logger::LogError(TEXT("Invalid Graphics Backend API type!"));
				break;
			}
		}
		
		void Engine::InitializeBackend(bool enableValidation)
		{
			GetCommandQueue()->PushCommand<Commands::InitializeBackend>(Commands::InitializeBackend(enableValidation));
		}
	}
}