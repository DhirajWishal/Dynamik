#include "dmkafx.h"
#include "VulkanRBL.h"

#include "Common/VulkanUtilities.h"
#include "Context/Attachments/VulkanColorAttachment.h"
#include "Context/Attachments/VulkanDepthAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanRBL::setMsaaSamples(const DMKSampleCount& samples)
		{
			myMsaaSampleCount = samples;
		}

		void VulkanRBL::setWindowHandle(const POINTER<DMKWindowHandle>& windowHandle)
		{
			baseWindowHandle = windowHandle;
		}
		
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

			if (myMsaaSampleCount > (DMKSampleCount)myDevice.getMaxUsableSampleCount())
			{
				DMKErrorManager::issueWarnBox("Pre defined samples are not supported by the GPU. Setting the default to the maximum usable count.");
				myMsaaSampleCount = (DMKSampleCount)myDevice.getMaxUsableSampleCount();
			}

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
			VulkanRenderPassSubpass _subPass;

			switch (contextType)
			{
			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT:
			{
				/* Initialize sub passes */
				VulkanRenerPassAtachmentDescription _description;
				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
				_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				FBAttachmentInitInfo.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.swapChainExtent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.swapChainExtent.width;

				auto _colorAttachment = StaticAllocator<VulkanColorAttachment>::allocate();
				_colorAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_colorAttachment);

				FBAttachmentInitInfo.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;

				auto _depthAttachment = StaticAllocator<VulkanDepthAttachment>::allocate();
				_depthAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_depthAttachment);
			}
			break;

			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT_VR:
				break;

			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_2D:
			{
				/* Initialize sub passes */
				VulkanRenerPassAtachmentDescription _description;
				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				FBAttachmentInitInfo.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.swapChainExtent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.swapChainExtent.width;

				auto _colorAttachment = StaticAllocator<VulkanColorAttachment>::allocate();
				_colorAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_colorAttachment);
			}
			break;

			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_3D:
			{
				/* Initialize sub passes */
				VulkanRenerPassAtachmentDescription _description;
				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
				_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				FBAttachmentInitInfo.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.swapChainExtent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.swapChainExtent.width;

				auto _colorAttachment = StaticAllocator<VulkanColorAttachment>::allocate();
				_colorAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_colorAttachment);

				FBAttachmentInitInfo.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;

				auto _depthAttachment = StaticAllocator<VulkanDepthAttachment>::allocate();
				_depthAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_depthAttachment);
			}
			break;

			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG:
			{
				/* Initialize sub passes */
				VulkanRenerPassAtachmentDescription _description;
				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
				_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.swapChainImageFormat;
				FBAttachmentInitInfo.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.swapChainExtent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.swapChainExtent.width;

				auto _colorAttachment = StaticAllocator<VulkanColorAttachment>::allocate();
				_colorAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_colorAttachment);

				FBAttachmentInitInfo.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;

				auto _depthAttachment = StaticAllocator<VulkanDepthAttachment>::allocate();
				_depthAttachment->initialize(myDevice, myQueues, FBAttachmentInitInfo);
				newContext.FBAttachments.pushBack(_depthAttachment);
			}
			break;

			case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG_VR:
				break;

			default:
				DMK_ERROR_BOX("Invalid context type!");
				break;
			}
			newContext.vRenderPass.initialize(myDevice, { _subPass });

			/* Create the frame buffer */
			newContext.vFrameBuffer.initialize(myDevice, newContext.vSwapChain, newContext.vRenderPass, newContext.FBAttachments);

			myActiveContexts.pushBack(newContext);
		}

		void VulkanRBL::terminateRenderingContext()
		{
			for (auto _context : myActiveContexts)
			{
				for (auto _attachment : _context.FBAttachments)
				{
					_attachment->terminate(myDevice);
					StaticAllocator<VulkanFrameBufferAttachment>::deallocate(_attachment, 0);
				}

				_context.vFrameBuffer.terminate(myDevice);
				_context.vRenderPass.terminate(myDevice);
				_context.vSwapChain.terminate(myDevice);
			}
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
			return ARRAY<VulkanRenderPassSubpass>();
		}
	}
}