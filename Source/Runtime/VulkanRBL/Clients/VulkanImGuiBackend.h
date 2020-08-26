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

			virtual void setContext(ImGuiContext* pContext) override final;

			virtual void initialize() override final;
			virtual void update() override final;
			virtual void drawFrame() override final;
			virtual void terminate() override final;

			virtual void bindCommands(RCommandBuffer* pCommandBuffer) override final;

			virtual void reCreatePipeline(RRenderTarget* pRenderTarget, DMKViewport viewport) override final;

			virtual void updateResources() override final;
			virtual void onRendererUpdate(const UI64 activeFrameIndex, RSwapChain* pSwapChain, RCommandBuffer* pActiveCommandBuffer) override final;

		private:
			void _initializeFontTexture();
			void _initializePipeline();
			void _initializeCommandBuffers();

			RColorBlendState createColorBlendState();
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IM_GUI_CLIENT_H
