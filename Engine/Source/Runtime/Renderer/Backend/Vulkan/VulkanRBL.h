#pragma once
#ifndef _DYNAMIK_VULKAN_RBL_H
#define _DYNAMIK_VULKAN_RBL_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "../RendererBackendLayer.h"

#include "Common/VulkanInstance.h"
#include "Common/VulkanSurface.h"
#include "Common/VulkanDevice.h"
#include "Common/VulkanQueue.h"
#include "Common/VulkanDescriptorSetManager.h"

#include "Context/VulkanSwapChain.h"
#include "Context/VulkanRenderPass.h"
#include "Context/VulkanFrameBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Render Context container
		*/
		struct DMK_API VulkanRenderContext {
			DMKRenderContextType type = DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT;

			VulkanViewport vViewport;
			VulkanSwapChain vSwapChain;
			VulkanRenderPass vRenderPass;
			VulkanFrameBuffer vFrameBuffer;

			ARRAY<POINTER<VulkanFrameBufferAttachment>> FBAttachments;
		};

		/*
		 Vulkan Renderer Backend Layer for the Dynamik Engine
		 This handles all the rendering backend tasks by using the Vulkan API.
		*/
		class DMK_API VulkanRBL : public DMKRendererBackendLayer {
		public:
			VulkanRBL() {}
			~VulkanRBL() {}

			void setMsaaSamples(const DMKSampleCount& samples) override;
			void setWindowHandle(const POINTER<DMKWindowHandle>& windowHandle) override;

			void initializeCore() override;
			void initializeRenderingContext(const DMKRenderContextType& contextType, const DMKViewport& viewport) override;

			void terminateRenderingContext() override;

		private:
			DMKSampleCount myMsaaSampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;

			VulkanInstance myInstance;
			VulkanSurface mySurface;
			VulkanDevice myDevice;
			VulkanQueue myQueues;

			POINTER<DMKWindowHandle> baseWindowHandle;

			/* Rendering Contexts */
			ARRAY<VulkanRenderContext> myActiveContexts;

			/*
			 Checks the current initialized contexts to see if the requested context is already initialized. The
			 function returns true if the requested context is not present in the store. Returns false if the 
			 requested context is already initialized.
			*/
			B1 _checkNewContextValidity(const DMKRenderContextType& type);

			/*
			 Return the render subpasses required for the render context
			*/
			ARRAY<VulkanRenderPassSubpass> _getRenderSubPass(const DMKRenderContextType& contextType);

			/* Descriptor Manager */
			VulkanDescriptorSetManager myActiveDescriptorManager;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_RBL_H
