// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IM_GUI_BACKEND_H
#define _DYNAMIK_VULKAN_IM_GUI_BACKEND_H

#include "Renderer/Clients/DMKImGuiBackend.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Im Gui Client
		*/
		class DMK_API VulkanImGuiBackend : public DMKImGuiBackend {
		public:
			VulkanImGuiBackend() {}
			~VulkanImGuiBackend() {}

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
