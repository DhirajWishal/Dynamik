#include "dmkafx.h"
#include "VulkanRBL.h"

#include "Common/VulkanUtilities.h"
#include "Common/VulkanPipelineManager.h"
#include "Context/Attachments/VulkanColorAttachment.h"
#include "Context/Attachments/VulkanDepthAttachment.h"

#include "Core/Math/MathFunctions.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

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
				DMKErrorManager::logWarn(DMK_TEXT("Pre defined samples are not supported by the GPU. Setting the default to the maximum usable count."));
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
				DMKErrorManager::logWarn(DMK_TEXT("Invalid viewport! (Window handle is not initialized)"));

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
			VulkanRenderAsset _asset;

			for (UI64 index = 0; index < entity->componentManager.getComponentArray<DMKMeshComponent>()->myComponents.size(); index++)
			{
				auto _meshComponent = entity->componentManager.getComponentArray<DMKMeshComponent>()->myComponents[index];

				VulkanRenderableMesh vMeshComponet;
				vMeshComponet.meshComponent = &entity->componentManager.getComponentArray<DMKMeshComponent>()->myComponents[index];

				/* Create vertex buffer */
				vMeshComponet.vertexOffset = vertexBufferSize;
				vertexBufferSize += _meshComponent.getVertexBufferObjectByteSize();

				/* Create index buffer */
				vMeshComponet.indexOffset = indexBufferSize;
				indexBufferSize += _meshComponent.getIndexBufferObjectByteSize();

				/* Create textures */
				ARRAY<VkDescriptorImageInfo> imageDescriptors;
				for (auto _texture : _meshComponent.textureModules)
				{
					VulkanTexture texture;
					texture.initialize(myDevice, myQueues, _texture);
					texture.initializeView(myDevice);
					texture.initializeSampler(myDevice);
					texture.makeRenderable(myDevice, myQueues);

					vMeshComponet.textures.pushBack(texture);
					imageDescriptors.pushBack(texture.createDescriptorInfo());
				}

				/* Create uniform buffer */
				UI32 bufferOffset = 0;
				ARRAY<std::pair<VkDescriptorBufferInfo, UI32>> bufferDescriptors;

				VulkanBuffer _uniformBuffer;
				_uniformBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_UNIFORM, _meshComponent.uniformDescription.getUniformSize());

				vMeshComponet.uniformBuffers.pushBack(_uniformBuffer);
				bufferDescriptors.pushBack({ _uniformBuffer.createDescriptorInfo(bufferOffset),  _meshComponent.uniformDescription.destinationBinding });

				for (auto _uniformDescription : _meshComponent.renderComponents)
				{
					_uniformBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_UNIFORM, _uniformDescription->uniformDescription.getUniformSize());

					vMeshComponet.uniformBuffers.pushBack(_uniformBuffer);
					bufferDescriptors.pushBack({ _uniformBuffer.createDescriptorInfo(bufferOffset), _uniformDescription->uniformDescription.destinationBinding });
				}

				//glm::mat4 _matrices[2];
				//_matrices[0] = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				//_matrices[1] = glm::perspective(DMKMathFunctions::radians(45.0f), (F32)myActiveContext.vViewport.width / (F32)myActiveContext.vViewport.height, 0.001f, 256.0f);
				//_matrices[1][1][1] *= -1.0f;
				//
				//MAT4F model = DMKMathFunctions::translate(MAT4F(1.0f), { 0.0f, 0.0f, 10.0f });
				//DMKMemoryFunctions::moveData(vMeshComponet.uniformBuffers[1].mapMemory(myDevice), &model, sizeof(MAT4F));
				//vMeshComponet.uniformBuffers[1].unmapMemory(myDevice);
				//
				//DMKMemoryFunctions::moveData(vMeshComponet.uniformBuffers[0].mapMemory(myDevice), _matrices, sizeof(MAT4F) * 2);
				//vMeshComponet.uniformBuffers[0].unmapMemory(myDevice);

				/* Resolve shaders */
				ARRAY<VulkanShader> vShaders;
				ARRAY<ARRAY<VkDescriptorSetLayoutBinding>> vDescriptorLayoutBindings;
				ARRAY<ARRAY<VkDescriptorPoolSize>> vDescriptorPoolSizes;
				for (auto _shader : _meshComponent.shaderModules)
				{
					VulkanShader _vShader;
					_vShader.initialize(myDevice, _shader);

					auto [bindings, sizes] = _vShader.createDescriptorLayoutAndSizes(myDevice);
					vDescriptorLayoutBindings.pushBack(bindings);
					vDescriptorPoolSizes.pushBack(sizes);

					vShaders.pushBack(_vShader);
				}

				/* Create descriptor */
				vMeshComponet.descriptor = myDescriptorManager.createDescriptor(myDevice, vDescriptorLayoutBindings, vDescriptorPoolSizes);
				myDescriptorManager.updateDescriptor(myDevice, vMeshComponet.descriptor.set, bufferDescriptors, imageDescriptors, vDescriptorLayoutBindings);

				/* Create pipeline */
				VulkanGraphicsPipelineInitInfo pipelineInitInfo;
				pipelineInitInfo.usage = _meshComponent.usage;
				pipelineInitInfo.vertexBufferDescriptor = _meshComponent.vertexDescriptor;

				pipelineInitInfo.viewports = { myActiveContext.vViewport };
				pipelineInitInfo.vRenderPass = myActiveContext.vRenderPass;
				pipelineInitInfo.swapChainExtent = myActiveContext.vSwapChain.extent;
				pipelineInitInfo.shaders = vShaders;

				pipelineInitInfo.descriptorLayouts = { vMeshComponet.descriptor.layout };

				pipelineInitInfo.multisamplerMsaaSamples = (VkSampleCountFlagBits)myMsaaSampleCount;
				vMeshComponet.pipeline = myPipelineManager.createGraphicsPipeline(myDevice, pipelineInitInfo);

				_asset.meshes.pushBack(vMeshComponet);
			}

			submitPendingAsset.pushBack(_asset);
		}

		void VulkanRBL::initializeLevel(POINTER<DMKLevelComponent> level)
		{
			return;	/* Until the game package pipeline is properly fixed and this function is fully functional */
		}

		void VulkanRBL::initializeFinalComponents()
		{
			_initializeBuffers();

			myActiveContext.vCommandBuffer.initializeCommandPool(myDevice, myQueues);
			myActiveContext.vCommandBuffer.allocateCommandBuffers(myDevice, myActiveContext.vSwapChain.images.size());

			VkCommandBuffer _buffer = VK_NULL_HANDLE;
			for (UI32 index = 0; index < myActiveContext.vSwapChain.images.size(); index++)
			{
				_buffer = myActiveContext.vCommandBuffer.beginCommandBufferRecording(myDevice, index);
				myActiveContext.vCommandBuffer.beginRenderPass(myDevice, myActiveContext.vRenderPass, myActiveContext.vFrameBuffer, myActiveContext.vSwapChain, index);

				VkDeviceSize _offsets[1] = { 0 };
				vkCmdBindVertexBuffers(_buffer, 0, 1, &myActiveVertexBuffer.buffer, _offsets);
				vkCmdBindIndexBuffer(_buffer, myActiveIndexBuffer, 0, VK_INDEX_TYPE_UINT32);

				for (auto _asset : submitPendingAsset)
				{
					for (auto _mesh : _asset.meshes)
					{
						vkCmdBindPipeline(_buffer, _mesh.pipeline.bindPoint, _mesh.pipeline.pipeline);

						vkCmdBindDescriptorSets(_buffer, _mesh.pipeline.bindPoint, _mesh.pipeline.layout, 0, 1, &_mesh.descriptor.set, 0, nullptr);

						vkCmdDrawIndexed(_buffer, _mesh.meshComponent->indexBufferObject.size(), 1, _mesh.indexOffset, _mesh.vertexOffset, 0);
					}
				}

				myActiveContext.vCommandBuffer.endRenderPass(_buffer);
				myActiveContext.vCommandBuffer.endCommandBufferRecording(myDevice, _buffer);
			}

			inFlightAsset = submitPendingAsset;
			submitPendingAsset.clear();

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

			for (auto _asset : inFlightAsset)
			{
				for (auto _mesh : _asset.meshes)
				{
					for (UI32 index = 0; index < _mesh.uniformBuffers.size(); index++)
					{
						if (_mesh.meshComponent->uniformDescription.usage == DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_MODEL)
						{
							MAT4F model = DMKMathFunctions::translate(MAT4F(1.0f), { 0.0f, 0.0f, 10.0f });
							DMKMemoryFunctions::moveData(_mesh.uniformBuffers[index].mapMemory(myDevice), &model, sizeof(MAT4F));
							_mesh.uniformBuffers[index].unmapMemory(myDevice);
						}
						else if (_mesh.meshComponent->renderComponents[index]->uniformDescription.usage == DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_CAMERA)
						{
							glm::mat4 _matrices[2];
							_matrices[0] = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
							_matrices[1] = glm::perspective(DMKMathFunctions::radians(45.0f), (F32)myActiveContext.vViewport.width / (F32)myActiveContext.vViewport.height, 0.001f, 256.0f);
							_matrices[1][1][1] *= -1.0f;

							DMKMemoryFunctions::moveData(_mesh.uniformBuffers[index].mapMemory(myDevice), _matrices, sizeof(MAT4F) * 2);
							_mesh.uniformBuffers[index].unmapMemory(myDevice);
						} 
					}
				}
			}
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

		void VulkanRBL::_initializeBuffers()
		{
			/* Create vertex buffer */
			myActiveVertexBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_VERTEX, vertexBufferSize);
			POINTER<BYTE> vertexPtr = myActiveVertexBuffer.mapMemory(myDevice);

			for (auto _asset : submitPendingAsset)
				for (auto _mesh : _asset.meshes)
					_mesh.meshComponent->packData((vertexPtr + _mesh.vertexOffset));

			myActiveVertexBuffer.unmapMemory(myDevice);

			/* Create index buffer */
			myActiveIndexBuffer.initialize(myDevice, BufferType::BUFFER_TYPE_INDEX, indexBufferSize);
			POINTER<BYTE> indexPtr = myActiveIndexBuffer.mapMemory(myDevice);

			for (auto _asset : submitPendingAsset)
				for (auto _mesh : _asset.meshes)
					DMKMemoryFunctions::moveData(indexPtr + _mesh.indexOffset, _mesh.meshComponent->indexBufferObject.data(), _mesh.meshComponent->getIndexBufferObjectByteSize());

			myActiveIndexBuffer.unmapMemory(myDevice);
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