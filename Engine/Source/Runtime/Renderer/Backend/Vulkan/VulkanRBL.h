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
		};

		/*
		 Vulkan Renderer Backend Layer for the Dynamik Engine
		 This handles all the rendering backend tasks by using the Vulkan API.
		*/
		class DMK_API VulkanRBL : public DMKRendererBackendLayer {
		public:
			VulkanRBL() {}
			~VulkanRBL() {}

			void initializeCore() override;
			void initializeRenderingContext(const DMKRenderContextType& contextType, const DMKViewport& viewport) override;

		private:
			VulkanInstance myInstance;
			VulkanSurface mySurface;
			VulkanDevice myDevice;
			VulkanQueue myQueues;

			POINTER<GLFWwindow> baseWindowHandle;

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
		};
	}
}

#endif // !_DYNAMIK_VULKAN_RBL_H
