// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IM_GUI_BACKEND_H
#define _DYNAMIK_VULKAN_IM_GUI_BACKEND_H

#include "Renderer/Clients/RImGuiBackend.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Im Gui Client
		*/
		class DMK_API VulkanImGuiBackend : public RImGuiBackend {
		public:
			VulkanImGuiBackend() {}
			~VulkanImGuiBackend() {}

			virtual void initialize() override final;
			virtual void update(ImDrawData* pDrawData) override final;
			virtual void drawFrame() override final;
			virtual void terminate() override final;

			virtual void bindCommands(RCommandBuffer* pCommandBuffer) override final;

			virtual void reCreatePipeline(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, DMKViewport viewport) override final;

		private:
			void _initializeFontTexture();
			void _initializePipeline();

			RColorBlendState createColorBlendState();
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IM_GUI_CLIENT_H
