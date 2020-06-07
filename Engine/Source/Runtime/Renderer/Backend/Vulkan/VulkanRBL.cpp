#include "dmkafx.h"
#include "VulkanRBL.h"

#include "Common/VulkanUtilities.h"
#include "Common/VulkanPipelineManager.h"
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
			myQueues.findQueueFamilies(myDevice, mySurface);
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
			if (mySurface.windowID != viewport.windowHandle.getPointerAsInteger())
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
			newContext.vViewport = _viewport;

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
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
				_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.format;
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.extent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.extent.width;

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
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.format;
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.extent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.extent.width;

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
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
				_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.format;
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.extent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.extent.width;

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
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
				_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(myDevice);
				_description.msaaSamples = myMsaaSampleCount;
				_subPass.attachments.pushBack(_description);

				_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
				_description.format = (DMKFormat)newContext.vSwapChain.format;
				_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
				_subPass.attachments.pushBack(_description);

				/* Add attachments */
				VulkanFrameBufferAttachmentInitInfo FBAttachmentInitInfo;
				FBAttachmentInitInfo.format = (DMKFormat)newContext.vSwapChain.format;
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
				FBAttachmentInitInfo.imageHeight = newContext.vSwapChain.extent.height;
				FBAttachmentInitInfo.imageWidth = newContext.vSwapChain.extent.width;

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

			//myActiveContexts.pushBack(newContext);
			myActiveContext = newContext;
		}

		void VulkanRBL::initializeEntity(POINTER<DMKGameEntity> entity)
		{
			for (auto _meshComponent : entity->componentManager.getComponentArray<DMKMeshComponent>()->myComponents)
			{
				VulkanRenderableMesh vMeshComponet;

				/* Create vertex buffer */
				vMeshComponet.vertexBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_VERTEX, _meshComponent.getVertexBufferObjectByteSize());
				_meshComponent.packData(vMeshComponet.vertexBuffer.mapMemory(myDevice));
				vMeshComponet.vertexBuffer.unmapMemory(myDevice);
				vMeshComponet.vertexCount = _meshComponent.rawVertexBufferObject.size();

				/* Create index buffer */
				vMeshComponet.indexBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_INDEX, _meshComponent.getIndexBufferObjectByteSize());
				DMKMemoryFunctions::moveData(vMeshComponet.indexBuffer.mapMemory(myDevice), _meshComponent.indexBufferObject.data(), _meshComponent.indexBufferObject.typeSize() * _meshComponent.indexBufferObject.size());
				vMeshComponet.indexCount = _meshComponent.indexBufferObject.size();

				/* Create textures */

				/* Create uniform buffer */

				/* Create descriptor */

				/* Create pipeline */
				ARRAY<VulkanShader> vShaders;
				for (auto _shader : _meshComponent.renderSpecifications.shaderModules)
				{
					VulkanShader _vShader;
					_vShader.initialize(myDevice, _shader);
					vShaders.pushBack(_vShader);
				}

				VulkanGraphicsPipelineInitInfo pipelineInitInfo;
				pipelineInitInfo.usage = _meshComponent.usage;
				pipelineInitInfo.vertexBufferDescriptor = _meshComponent.vertexDescriptor;

				pipelineInitInfo.viewports = { myActiveContext.vViewport };
				pipelineInitInfo.vRenderPass = myActiveContext.vRenderPass;
				pipelineInitInfo.swapChainExtent = myActiveContext.vSwapChain.extent;
				pipelineInitInfo.shaders = vShaders;

				pipelineInitInfo.multisamplerMsaaSamples = (VkSampleCountFlagBits)myMsaaSampleCount;
				VulkanPipelineManager vPipelineManager;
				vMeshComponet.pipeline = vPipelineManager.createGraphicsPipeline(myDevice, pipelineInitInfo);
			
				submitPendingMeshes.pushBack(vMeshComponet);
			}
		}

		void VulkanRBL::initializeEntities(ARRAY<POINTER<DMKGameEntity>> entities)
		{
			return;	/* Until the game package pipeline is properly fixed and this function is fully functional */
		}

		void VulkanRBL::initializeFinalComponents()
		{
			myActiveContext.vCommandBuffer.initializeCommandPool(myDevice, myQueues);
			myActiveContext.vCommandBuffer.allocateCommandBuffers(myDevice, myActiveContext.vSwapChain.images.size());

			VkCommandBuffer _buffer = VK_NULL_HANDLE;
			for (UI32 index = 0; index < myActiveContext.vSwapChain.images.size(); index++)
			{
				_buffer = myActiveContext.vCommandBuffer.beginCommandBufferRecording(myDevice, index);
				myActiveContext.vCommandBuffer.beginRenderPass(myDevice, myActiveContext.vRenderPass, myActiveContext.vFrameBuffer, myActiveContext.vSwapChain, index);

				for (auto _mesh : submitPendingMeshes)
				{
					vkCmdBindPipeline(_buffer, _mesh.pipeline.bindPoint, _mesh.pipeline.pipeline);

					VkDeviceSize _offsets[1] = { 0 };

					vkCmdBindVertexBuffers(_buffer, 0, 1, &_mesh.vertexBuffer.buffer, _offsets);
					//vkCmdDraw(_buffer, _asset.vertexCount, 1, 0, 0);

					vkCmdBindIndexBuffer(_buffer, _mesh.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

					vkCmdDrawIndexed(_buffer, _mesh.indexCount, 1, 0, 0, 0);
				}

				myActiveContext.vCommandBuffer.endRenderPass(_buffer);
				myActiveContext.vCommandBuffer.endCommandBufferRecording(myDevice, _buffer);
			}

			inFlightMeshes = submitPendingMeshes;
			submitPendingMeshes.clear();

			if (!isSyncObjectsInitialized)
				myActiveContext.vSyncObjects.initialize(myDevice);

			readyToDraw = true;
		}

		void VulkanRBL::initializeDrawCall()
		{
			if (!readyToDraw)
				return;

			/* Sync the inflight fence */
			myActiveContext.vSyncObjects.syncFence(myDevice);

			/* Get the next image index */
			imageIndex = myActiveContext.vSyncObjects.getNextImage(myDevice, myActiveContext.vSwapChain);
			frameResult = myActiveContext.vSyncObjects.getResult();

			/* Check if any errors were encountered */
			if (frameResult == VK_ERROR_OUT_OF_DATE_KHR)
			{
				//recreateSwapChain();
				return;
			}
			else if (frameResult != VK_SUCCESS && frameResult != VK_SUBOPTIMAL_KHR)
				DMK_ERROR_BOX("Failed to acquire Swap Chain image!");
		}

		void VulkanRBL::updateRenderables()
		{
			if (!readyToDraw)
				return;
		}

		void VulkanRBL::submitRenderables()
		{
			if (!readyToDraw)
				return;

			/* Submit commands */
			myActiveContext.vSyncObjects.submitCommands(myDevice, myQueues, myActiveContext.vSwapChain, myActiveContext.vCommandBuffer);

			/* Increment the frame counter */
			myActiveContext.vSyncObjects++;
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