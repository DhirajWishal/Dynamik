// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Renderer.h"

/* Vulkan headers */
#include "Backend/Vulkan/VulkanCoreObject.h"
#include "Backend/Vulkan/Common/VulkanInstance.h"
#include "Backend/Vulkan/Common/VulkanSurface.h"
#include "Backend/Vulkan/Common/VulkanDevice.h"
#include "Backend/Vulkan/Common/VulkanQueue.h"
#include "Backend/Vulkan/Common/VulkanCommandBuffer.h"
#include "Backend/Vulkan/Common/VulkanCommandBufferManager.h"
#include "Backend/Vulkan/Common/VulkanDescriptorSetManager.h"
#include "Backend/Vulkan/Context/VulkanSwapChain.h"
#include "Backend/Vulkan/Context/VulkanRenderPass.h"
#include "Backend/Vulkan/Context/VulkanFrameBuffer.h"
#include "Backend/Vulkan/Graphics/VulkanRenderAsset.h"
#include "Backend/Vulkan/Pipelines/VulkanGraphicsPipeline.h"

namespace Dynamik
{
	using namespace Backend;

	/* ---------- CLASS DEFINITION ---------- */
	void DMKRenderer::initialize()
	{
		myCompatibility.isVulkanAvailable = glfwVulkanSupported();

		myAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
		myRenderTarget = new RRenderTarget;

		//myRenderer.setMsaaSamples(DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT);
		//myRenderer.initialize();
		DMK_INFO("Entered the renderer thread!");
	}

	void DMKRenderer::processCommand(DMKThreadCommand* pCommand)
	{
		myCommand = Inherit<DMKRendererCommand>(pCommand);

		switch (myCommand->instruction)
		{
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE:

#ifdef DMK_DEBUG
			myCoreObject = createCore(true);

#else
			myCoreObject = createCore(false);

#endif // DMK_DEBUG
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_CREATE_CONTEXT:
			createContext(Inherit<RendererCreateContextCommand>(myCommand)->contextType, Inherit<RendererCreateContextCommand>(myCommand)->viewport);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS:
			initializeFinals();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITY:
			createEntityResources(Inherit<RendererAddEntity>(myCommand)->entity);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_LEVEL:
			//myBackend.initializeLevel(DMKLevelComponent*());
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SUBMIT_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_INITIALIZE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE:
			//myBackend.initializeDrawCall();
			//myBackend.updateRenderables();
			//myBackend.submitRenderables();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_SUBMIT:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_FRAME:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_UPDATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_SAMPLES:
			setSamples(Inherit<RendererSetSamplesCommand>(myCommand)->samples);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_WINDOW_HANDLE:
			setWindowHandle(Inherit<RendererSetWindowHandleCommand>(myCommand)->windowHandle);
			break;
		default:
			break;
		}
	}

	void DMKRenderer::onLoop()
	{
		if (!isInitialized)
			return;

		myCoreObject->submitCommand(myCommandBuffers[myCoreObject->prepareFrame(mySwapChain)], mySwapChain);
	}

	void DMKRenderer::onTermination()
	{
		terminateComponents();

		StaticAllocator<VulkanCoreObject>::deallocate(myCoreObject, 0);

		StaticAllocator<RSwapChain>::deallocate(mySwapChain, 0);
		StaticAllocator<RRenderPass>::deallocate(myRenderTarget->pRenderPass, 0);
		StaticAllocator<RFrameBuffer>::deallocate(myRenderTarget->pFrameBuffer, 0);
		StaticAllocator<RRenderTarget>::deallocate(myRenderTarget, 0);

		StaticAllocator<RCommandBufferManager>::deallocate(myCommandBufferManager, 0);

		for (auto buffer : myCommandBuffers)
			StaticAllocator<RCommandBuffer>::deallocate(buffer, 0);

		DMK_INFO("Terminated the renderer thread!");
	}

	/* ---------- INTERNAL METHODS ---------- */
	void DMKRenderer::setSamples(const DMKSampleCount& samples)
	{
		mySampleCount = samples;
	}

	void DMKRenderer::setWindowHandle(const DMKWindowHandle* windowHandle)
	{
		myWindowHandle = Cast<DMKWindowHandle*>(windowHandle);
	}

	RCoreObject* DMKRenderer::createCore(B1 bEnableValidation)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myCoreObject = Inherit<RCoreObject>(StaticAllocator<VulkanCoreObject>::allocate().get());
			myCoreObject->initialize(myWindowHandle, mySampleCount, bEnableValidation);
		}
		break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			DMK_ERROR_BOX("Invalid rendering API!");
			break;
		}

		myBufferFactory.setDefaults(myAPI, myCoreObject);

		return myCoreObject;
	}

	RSwapChain* DMKRenderer::createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			mySwapChain = Inherit<RSwapChain>(StaticAllocator<VulkanSwapChain>::allocate().get());
			mySwapChain->initialize(myCoreObject, viewport, presentMode);
		}
		break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			DMK_ERROR_BOX("Invalid rendering API!");
			break;
		}

		return mySwapChain;
	}

	RRenderPass* DMKRenderer::createRenderPass(ARRAY<RSubPasses> subPasses)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myRenderTarget->pRenderPass = Inherit<RRenderPass>(StaticAllocator<VulkanRenderPass>::allocate().get());
			
			/* Attachments: Color, Depth, Swap Chain */
			myRenderTarget->pRenderPass->initialize(myCoreObject, subPasses, mySwapChain);
		}
		break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			DMK_ERROR_BOX("Invalid rendering API!");
			break;
		}

		return myRenderTarget->pRenderPass;
	}

	RFrameBuffer* DMKRenderer::createFrameBuffer()
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myRenderTarget->pFrameBuffer = Inherit<RFrameBuffer>(StaticAllocator<VulkanFrameBuffer>::allocate().get());
			myRenderTarget->pFrameBuffer->initialize(myCoreObject, myRenderTarget->pRenderPass, mySwapChain);
		}
		break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			DMK_ERROR_BOX("Invalid rendering API!");
			break;
		}

		return myRenderTarget->pFrameBuffer;
	}

	void DMKRenderer::createContext(DMKRenderContextType type, DMKViewport viewport)
	{
		/* Initialize Swap chain */
		createSwapChain(viewport, RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_FIFO);

		/* Initialize Render pass */
		ARRAY<RSubPasses> subpasses;
		switch (type)
		{
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT:
			subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT_VR:
			subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_2D:
			subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_SWAPCHAIN };
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_3D:
			subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG:
			subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG_VR:
			subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
			break;
		default:
			DMK_ERROR_BOX("Invalid context type!");
			break;
		}

		createRenderPass(subpasses);

		/* Initialize Frame buffer */
		createFrameBuffer();
	}

	RBuffer* DMKRenderer::createBuffer(const RBufferType& type, UI64 size)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			VulkanBuffer* pBuffer = StaticAllocator<VulkanBuffer>::allocate();
			pBuffer->initialize(myCoreObject, type, size);

			return Cast<RBuffer*>(pBuffer);
		}
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			break;
		}

		return nullptr;
	}

	RTexture* DMKRenderer::createTexture(const DMKTexture* pTexture)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			RTexture* texture = Inherit<RTexture>(StaticAllocator<VulkanTexture>::allocate().get());
			texture->initialize(myCoreObject, (DMKTexture*)pTexture);
			texture->createView(myCoreObject);

			RImageSamplerCreateInfo samplerCreateInfo;
			texture->createSampler(myCoreObject, samplerCreateInfo);

			return texture;
		}
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			break;
		}

		return nullptr;
	}

	RPipelineObject* DMKRenderer::allocatePipeline()
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
			return Inherit<RPipelineObject>(StaticAllocator<VulkanGraphicsPipeline>::allocate().get());
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			break;
		}

		return nullptr;
	}

	void DMKRenderer::createEntityResources(DMKGameEntity* pGameEntity)
	{
		REntity entity;
		RMeshObject* meshComponent = nullptr;
		for (UI64 index = 0; index < pGameEntity->componentManager.getComponentArray<DMKMeshComponent>()->myComponents.size(); index++)
		{
			auto mesh = pGameEntity->componentManager.getComponent<DMKMeshComponent>(index);
			meshComponent = StaticAllocator<RMeshObject>::allocate();
			meshComponent->pMeshComponent = mesh;

			/* Initialize Vertex Data */
			meshComponent->vertexBufferOffset = myVertexBufferByteSize;
			myVertexBufferByteSize += mesh->getVertexBufferObjectByteSize();

			/* Initialize Index Data */
			meshComponent->indexBufferOffset = myIndexBufferByteSize;
			myIndexBufferByteSize += mesh->getIndexBufferObjectByteSize();

			/* Initialize Texture Data */
			for (auto pTexture : mesh->textureModules)
				meshComponent->pTextures.pushBack(createTexture(pTexture));

			/* Initialize Uniform Buffers */

			/* Initialize Pipeline */
			meshComponent->pPipeline = allocatePipeline();

			RPipelineCreateInfo pipelineCreateInfo = {};
			pipelineCreateInfo.pRenderTarget = myRenderTarget;
			pipelineCreateInfo.pSwapChain = mySwapChain;
			pipelineCreateInfo.shaders = mesh->shaderModules;
			pipelineCreateInfo.scissorInfos.resize(1);
			pipelineCreateInfo.colorBlendInfo.blendStates = createBasicBlendStates();
			pipelineCreateInfo.multiSamplingInfo.sampleCount = myCoreObject->sampleCount;
			meshComponent->pPipeline->initialize(myCoreObject, pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS);

			entity.pMeshObjects.pushBack(meshComponent);
		}

		myEntities.pushBack(entity);
	}

	void DMKRenderer::initializeBuffers()
	{
		POINTER<BYTE> bufferDataPointer;

		/* Initialize Vertex Buffer */
		myVertexBuffer = createBuffer(RBufferType::BUFFER_TYPE_VERTEX, myVertexBufferByteSize);
		for (auto entity : myEntities)
		{
			bufferDataPointer = myVertexBuffer->getData(myCoreObject, myVertexBufferByteSize, 0);
			for (auto mesh : entity.pMeshObjects)
			{
				/* ---------- DEBUG ---------- */
				struct TempVertex {
					TempVertex() {}
					TempVertex(const Vector3F& position, const Vector3F& color) : position(position), color(color) {}
					~TempVertex() {}

					Vector3F position;
					Vector3F color;
				};

				ARRAY<TempVertex> vertexes = {
					TempVertex({ 0.0f,	0.5f,  -1.0f }, { 1.f, 0.0f, 0.0f }),
					TempVertex({ 0.5f,  -0.5f, -1.0f }, { 1.f, 1.0f, 0.0f }),
					TempVertex({ -0.5f, -0.5f, -1.0f }, { 1.f, 1.0f, 1.0f }),
				};

				DMKMemoryFunctions::moveData(bufferDataPointer.get(), vertexes.data(), mesh->pMeshComponent->getVertexBufferObjectByteSize());
				//DMKMemoryFunctions::moveData(bufferDataPointer.get(), mesh->pMeshComponent->vertexBuffer, mesh->pMeshComponent->getVertexBufferObjectByteSize());
				bufferDataPointer += mesh->pMeshComponent->getVertexBufferObjectByteSize();

				mesh->pMeshComponent->clearVertexBuffer();
			}
			myVertexBuffer->unmapMemory(myCoreObject);
		}

		/* Initialize Index Buffer */
		myIndexBuffer = createBuffer(RBufferType::BUFFER_TYPE_INDEX, myIndexBufferByteSize);
		for (auto entity : myEntities)
		{
			bufferDataPointer = myIndexBuffer->getData(myCoreObject, myIndexBufferByteSize, 0);
			for (auto mesh : entity.pMeshObjects)
			{
				/* ---------- DEBUG ---------- */
				ARRAY<UI32> indexes = {
					0, 1, 2
				};

				DMKMemoryFunctions::moveData(bufferDataPointer.get(), indexes.data(), mesh->pMeshComponent->getIndexBufferObjectByteSize());
				//DMKMemoryFunctions::moveData(bufferDataPointer.get(), mesh->pMeshComponent->indexBuffer.data(), mesh->pMeshComponent->getIndexBufferObjectByteSize());
				bufferDataPointer += mesh->pMeshComponent->getIndexBufferObjectByteSize();

				mesh->pMeshComponent->clearIndexBuffer();
			}
			myIndexBuffer->unmapMemory(myCoreObject);
		}
	}

	void DMKRenderer::initializeFinals()
	{
		initializeBuffers();

		myCommandBufferManager = Inherit<RCommandBufferManager>(StaticAllocator<VulkanCommandBufferManager>::allocate().get());
		myCommandBufferManager->initialize(myCoreObject);
		myCommandBuffers = myCommandBufferManager->allocateCommandBuffers(myCoreObject, mySwapChain->bufferCount);

		UI64 firstIndex = 0;
		UI64 firstVertex = 0;

		for (UI32 itr = 0; itr < myCommandBuffers.size(); itr++)
		{
			auto buffer = myCommandBuffers[itr];
			buffer->begin();

			myCommandBufferManager->bindRenderTarget(buffer, myRenderTarget, mySwapChain, itr);

			buffer->bindVertexBuffer(myVertexBuffer, 0);
			buffer->bindIndexBuffer(myIndexBuffer);

			firstIndex = 0;
			firstVertex = 0;

			for (auto entity : myEntities)
			{
				for (auto mesh : entity.pMeshObjects)
				{
					buffer->bindGraphicsPipeline(mesh->pPipeline);
					buffer->drawIndexed(firstIndex, mesh->vertexBufferOffset, mesh->pMeshComponent->indexCount, 1);
					//buffer->drawVertexes(firstVertex, mesh->pMeshComponent->vertexCount, 1);

					firstIndex += mesh->pMeshComponent->indexCount;
					firstVertex += mesh->pMeshComponent->vertexCount;
				}
			}

			myCommandBufferManager->unbindRenderTarget(buffer);

			buffer->end();
		}

		isInitialized = true;
	}

	void DMKRenderer::terminateComponents()
	{
		myCoreObject->idleCall();

		/* Terminate Command Buffers */
		myCommandBufferManager->terminate(myCoreObject, myCommandBuffers);
		StaticAllocator<RCommandBufferManager>::deallocate(myCommandBufferManager, 0);

		/* Terminate Swap Chain */
		mySwapChain->terminate(myCoreObject);
		StaticAllocator<RSwapChain>::deallocate(mySwapChain, 0);

		/* Terminate Render Pass */
		myRenderTarget->pRenderPass->terminate(myCoreObject);
		StaticAllocator<RRenderPass>::deallocate(myRenderTarget->pRenderPass, 0);

		/* Terminate Frame Buffer */
		myRenderTarget->pFrameBuffer->terminate(myCoreObject);
		StaticAllocator<RFrameBuffer>::deallocate(myRenderTarget->pFrameBuffer, 0);

		/* Terminate Core Object */
		myCoreObject->terminate();
		StaticAllocator<RCoreObject>::deallocate(myCoreObject, 0);
	}

	void DMKRenderer::terminateEntities()
	{
		for (auto entity : myEntities)
		{
			for (auto mesh : entity.pMeshObjects)
			{
				StaticAllocator<RPipelineObject>::deallocate(mesh->pPipeline, 0);

				StaticAllocator<RMeshObject>::deallocate(mesh);
			}

			entity.pMeshObjects.clear();
		}

		myEntities.clear();
	}

	ARRAY<RColorBlendState> DMKRenderer::createBasicBlendStates()
	{
		ARRAY<RColorBlendState> blendStates;
		RColorBlendState state;
		for (UI32 index = 0; index < 1; index++)
		{
			state.colorWriteMask = (RColorComponent)0;
			state.enable = false;

			blendStates.pushBack(state);
		}

		return blendStates;
	}
}
