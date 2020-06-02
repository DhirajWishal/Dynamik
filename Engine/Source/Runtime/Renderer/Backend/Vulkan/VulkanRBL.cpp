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
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
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
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
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
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
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
				FBAttachmentInitInfo.msaaSamples = myMsaaSampleCount;
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

			//myActiveContexts.pushBack(newContext);
			myActiveContext = newContext;
		}

		void VulkanRBL::initializeObject(POINTER<DMKMeshComponent> meshComponent)
		{
			struct _local {
				VEC3F position;
				VEC3F color;
			};

			ARRAY<_local> _vertexBufferObject;
			ARRAY<UI32> _indexBufferObject;

			_local _object;
			_object.color = { 1.0f, 1.0f, 1.0f };

			_object.position = { 0.0f, 1.0f, 0.0f };
			_vertexBufferObject.pushBack(_object);
			_indexBufferObject.pushBack(0);

			_object.position = { 1.0f, 0.0f, 0.0f };
			_vertexBufferObject.pushBack(_object);
			_indexBufferObject.pushBack(1);

			_object.position = { -1.0f, 0.0f, 0.0f };
			_vertexBufferObject.pushBack(_object);
			_indexBufferObject.pushBack(2);

			VulkanRenderAsset _asset;
			_asset.vertexBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_VERTEX, _vertexBufferObject.size() * sizeof(_local));
			memcpy(_asset.vertexBuffer.mapMemory(myDevice), _vertexBufferObject.data(), _vertexBufferObject.size() * sizeof(_local));
			_asset.vertexBuffer.unmapMemory(myDevice);
			_asset.vertexCount = _vertexBufferObject.size();

			_asset.indexBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_INDEX, _indexBufferObject.size() * sizeof(UI32));
			memcpy(_asset.indexBuffer.mapMemory(myDevice), _indexBufferObject.data(), _indexBufferObject.size() * sizeof(UI32));
			_asset.indexBuffer.unmapMemory(myDevice);
			_asset.indexCount = _indexBufferObject.size();

			DMKShaderModule vertexShaderModule;
			vertexShaderModule.codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV;
			vertexShaderModule.location = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
			vertexShaderModule.loadCode("E:/Projects/Dynamik Engine/Versions/DynamikEngine/Engine/Source/Studio/Assets/Shaders/Basic/vert.spv");
			VulkanShader vertexShader;
			vertexShader.initialize(myDevice, vertexShaderModule);

			DMKShaderModule fragmentShaderModule;
			fragmentShaderModule.codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV;
			fragmentShaderModule.location = DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT;
			fragmentShaderModule.loadCode("E:/Projects/Dynamik Engine/Versions/DynamikEngine/Engine/Source/Studio/Assets/Shaders/Basic/frag.spv");
			VulkanShader fragmentShader;
			fragmentShader.initialize(myDevice, fragmentShaderModule);

			DMKVertexBufferDescriptor vertexDescriptor;
			DMKVertexAttribute vertexAttribute;
			vertexAttribute.dataCount = 1;
			vertexAttribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
			vertexAttribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
			vertexDescriptor.attributes.pushBack(vertexAttribute);

			vertexAttribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR;
			vertexDescriptor.attributes.pushBack(vertexAttribute);

			VulkanGraphicsPipelineInitInfo initInfo;
			initInfo.shaders = { vertexShader, fragmentShader };
			initInfo.vertexBufferDescriptor = vertexDescriptor;
			initInfo.vRenderPass = myActiveContext.vRenderPass;
			initInfo.viewports = { myActiveContext.vViewport };
			initInfo.multisamplerMsaaSamples = (VkSampleCountFlagBits)myMsaaSampleCount;

			VulkanPipelineManager pipelineManager;
			_asset.pipeline = pipelineManager.createGraphicsPipeline(myDevice, initInfo);

			submitPendingAssets.pushBack(_asset);
		}

		void VulkanRBL::initializeFinalComponents()
		{
			myActiveContext.vCommandBuffer.initializeCommandPool(myDevice, myQueues);
			myActiveContext.vCommandBuffer.allocateCommandBuffers(myDevice, myActiveContext.vSwapChain.swapChainImages.size());

			VkCommandBuffer _buffer = VK_NULL_HANDLE;
			for (UI32 index = 0; index < myActiveContext.vSwapChain.swapChainImages.size(); index++)
			{
				_buffer = myActiveContext.vCommandBuffer.beginCommandBufferRecording(myDevice, index);
				myActiveContext.vCommandBuffer.beginRenderPass(myDevice, myActiveContext.vRenderPass, myActiveContext.vFrameBuffer, myActiveContext.vSwapChain, index);

				for (auto _asset : submitPendingAssets)
				{
					vkCmdBindPipeline(_buffer, _asset.pipeline.bindPoint, _asset.pipeline.pipeline);

					VkDeviceSize _offsets[1] = { 0 };

					vkCmdBindVertexBuffers(_buffer, 0, 1, &_asset.vertexBuffer.buffer, _offsets);
					//vkCmdDraw(_buffer, _asset.vertexCount, 1, 0, 0);

					vkCmdBindIndexBuffer(_buffer, _asset.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

					vkCmdDrawIndexed(_buffer, _asset.indexCount, 1, 0, 0, 0);
				}

				myActiveContext.vCommandBuffer.endRenderPass(_buffer);
				myActiveContext.vCommandBuffer.endCommandBufferRecording(myDevice, _buffer);
			}

			inFlightAssets = submitPendingAssets;
			submitPendingAssets.clear();

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