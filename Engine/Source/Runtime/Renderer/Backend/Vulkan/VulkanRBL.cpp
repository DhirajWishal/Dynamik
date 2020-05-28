#include "dmkafx.h"
#include "VulkanRBL.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanRBL::initializeCore()
		{
			/* Initialize the Vulkan Instance */
#ifdef DMK_DEBUG
			myInstance.initialize(true);

#else
			myInstance.initialize(false);

#endif

			/* Initialize the Vulkan Surface */
			mySurface.initialize(myInstance, baseWindowHandle);

			/* Initialize the Vulkan Device */
			myDevice.initialize(myInstance, mySurface);

			/* Initialize the Vulkan Queues */
			myQueues.initializeQueues(myDevice);
		}

		void VulkanRBL::initializeRenderingContext(const DMKRenderContextType& contextType, const DMKViewport& viewport)
		{
			/* Check for the context validity */
			if (!_checkNewContextValidity(contextType))
			{
				DMKErrorManager::issueWarnBox("Requested context already exists!");
				return;
			}

			/* Check if the passed window handle is initialized */
			if (mySurface.windowID != viewport.windowHandle.getAddressAsInteger())
				DMK_ERROR_BOX("Invalid viewport! (Window handle is not initialized)");

			/* Create the new viewport */
			VulkanViewport _viewport;
			_viewport.surfacePtr = &mySurface;
			_viewport.width = viewport.width;
			_viewport.height = viewport.height;
			_viewport.xOffset = viewport.xOffset;
			_viewport.yOffset = viewport.yOffset;

			/* Create new context */
			VulkanRenderContext newContext;
			newContext.type = contextType;

			/* Initialize swapchain */
			newContext.vSwapChain.initialize(myDevice, myQueues, _viewport);

			/* Initialize render pass */
			newContext.vRenderPass.initialize(myDevice, _getRenderSubPass(contextType));
		}

		B1 VulkanRBL::_checkNewContextValidity(const DMKRenderContextType& type)
		{
			for (auto _context : myActiveContexts)
				if (_context.type == type)
					return false;

			return true;
		}
		
		ARRAY<VulkanRenderPassSubpass> VulkanRBL::_getRenderSubPass(const DMKRenderContextType& contextType)
		{
			switch (contextType)
			{
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT:
			{
				VulkanRenderPassSubpass _subPass;
				_subPass.attachments;
			}
				break;
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT_VR:
				break;
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_2D:
				break;
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_3D:
				break;
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG:
				break;
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG_VR:
				break;
			default:
				break;
			}
		}
	}
}