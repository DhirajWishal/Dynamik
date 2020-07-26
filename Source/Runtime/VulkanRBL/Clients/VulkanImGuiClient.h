// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IM_GUI_CLIENT_H
#define _DYNAMIK_VULKAN_IM_GUI_CLIENT_H

#include "Renderer/Clients/RImGuiClient.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Im Gui Client
		*/
		class DMK_API VulkanImGuiClient : public RImGuiClient {
		public:
			VulkanImGuiClient() {}
			~VulkanImGuiClient() {}

			virtual void initialize() override final;
			virtual void update() override final;
			virtual void drawFrame() override final;
			virtual void terminate() override final;

		private:
			void _initializeFontTexture();
			void _initializePipeline();

			RColorBlendState createColorBlendState();
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IM_GUI_CLIENT_H
