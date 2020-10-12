// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsEngine/Engine.h"
#include "Core/Error/ErrorManager.h"

namespace DMK
{
	namespace GraphicsEngine
	{
		void Engine::InitializeBackend(GraphicsCore::BackendAPI API, GraphicsCore::BackendInitInfo backendInitInfo)
		{
			switch (API)
			{
			case DMK::GraphicsCore::BackendAPI::BACKEND_API_VULKAN:
				break;
			case DMK::GraphicsCore::BackendAPI::BACKEND_API_DIRECTX_12:
				break;
			case DMK::GraphicsCore::BackendAPI::BACKEND_API_WEB_GPU:
				break;
			default:
				DMKErrorManager::logError(TEXT("Unsupported or invalid graphics backend API!"));
				break;
			}
		}
	}
}