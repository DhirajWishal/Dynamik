// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Backend/Instance.h"
#include "GraphicsCore/Backend/Interface/InstanceFunctions.h"
#include "Core/ErrorHandler/Logger.h"

#include "VulkanBackend/Exporter.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void Instance::Initialize(BackendAPI api, bool enableValidaion)
		{
			switch (api)
			{
			case DMK::GraphicsCore::BackendAPI::VULKAN:
				VulkanBackend::ExportFunctions();
				break;
			case DMK::GraphicsCore::BackendAPI::DIRECT_X_12:
				break;
			case DMK::GraphicsCore::BackendAPI::WEB_GPU:
				break;
			default:
				Logger::LogError(TEXT("Invalid or Undefined backend API type!"));
				break;
			}

			Interface::pfCreateInstance(&pInstanceData, enableValidaion);
		}
		
		void Instance::Terminate()
		{
			Interface::pfDestroyInstance(pInstanceData);
		}
	}
}
