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

	void DMKRenderer::processCommand(POINTER<DMKThreadCommand> command)
	{
		myCommand = (DMKRendererCommand*)command;

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
			createContext(((RendererCreateContextCommand*)myCommand)->contextType, ((RendererCreateContextCommand*)myCommand)->viewport);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS:
			initializeFinals();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITY:
			createEntityResources(((RendererAddEntity*)myCommand)->entity);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_LEVEL:
			//myBackend.initializeLevel(POINTER<DMKLevelComponent>());
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
			setSamples(((RendererSetSamplesCommand*)myCommand)->samples);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_WINDOW_HANDLE:
			setWindowHandle(((RendererSetWindowHandleCommand*)myCommand)->windowHandle);
			break;
		default:
			break;
		}
	}

	void DMKRenderer::onLoop()
	{
		if (!isInitialized)
			return;

		myCoreObject->submitCommand(myCommandBuffers[myCoreObject->prepareFrame(myRenderTarget->pSwapChain)], myRenderTarget->pSwapChain);
	}

	void DMKRenderer::onTermination()
	{
		terminateComponents();

		StaticAllocator<VulkanCoreObject>::deallocate(myCoreObject, 0);

		StaticAllocator<RSwapChain>::deallocate(myRenderTarget->pSwapChain, 0);
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

	void DMKRenderer::setWindowHandle(const POINTER<DMKWindowHandle>& windowHandle)
	{
		myWindowHandle = windowHandle;
	}

	POINTER<RCoreObject> DMKRenderer::createCore(B1 bEnableValidation)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			auto myPtr = StaticAllocator<VulkanCoreObject>::allocate();
			myPtr->initialize(myWindowHandle, mySampleCount, bEnableValidation);

			return myPtr;
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

	POINTER<RSwapChain> DMKRenderer::createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myRenderTarget->pSwapChain = (POINTER<RSwapChain>)StaticAllocator<VulkanSwapChain>::allocate();
			myRenderTarget->pSwapChain->initialize(myCoreObject, viewport, presentMode);
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

		return myRenderTarget->pSwapChain;
	}

	POINTER<RRenderPass> DMKRenderer::createRenderPass(ARRAY<RSubPasses> subPasses)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myRenderTarget->pRenderPass = (POINTER<RRenderPass>)StaticAllocator<VulkanRenderPass>::allocate();
			/* Attachments: SwapChain, Depth, Color */
			myRenderTarget->pRenderPass->initialize(myCoreObject, subPasses, myRenderTarget->pSwapChain);
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

	POINTER<RFrameBuffer> DMKRenderer::createFrameBuffer()
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myRenderTarget->pFrameBuffer = (POINTER<RFrameBuffer>)StaticAllocator<VulkanFrameBuffer>::allocate();
			myRenderTarget->pFrameBuffer->initialize(myCoreObject, myRenderTarget->pRenderPass, myRenderTarget->pSwapChain);
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

		ARRAY<RSubPasses> subpasses = { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };

		/* Initialize Render pass */
		switch (type)
		{
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT:
			createRenderPass(subpasses);
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT_VR:
			createRenderPass(subpasses);
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_2D:
			createRenderPass(subpasses);
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_3D:
			createRenderPass(subpasses);
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG:
			createRenderPass(subpasses);
			break;
		case Dynamik::DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG_VR:
			createRenderPass(subpasses);
			break;
		default:
			DMK_ERROR_BOX("Invalid context type!");
			break;
		}

		/* Initialize Frame buffer */
		createFrameBuffer();
	}

	void DMKRenderer::createEntityResources(POINTER<DMKGameEntity> pGameEntity)
	{
	}

	void DMKRenderer::initializeFinals()
	{
		/*
		 Initialize vertex buffers.
		 Copy vertex data from mesh to the vertex buffers.
		 Clear vertex data from the mesh.

		 Initialize index buffers.
		 Copy index data from mesh to the index buffers.
		 Clear index data from the mesh.
		*/

		myCommandBufferManager = (POINTER<RCommandBufferManager>)StaticAllocator<VulkanCommandBufferManager>::allocate();
		myCommandBufferManager->initialize(myCoreObject);
		myCommandBuffers = myCommandBufferManager->allocateCommandBuffers(myCoreObject, myRenderTarget->pSwapChain->images.size());

		for (UI32 itr = 0; itr < myCommandBuffers.size(); itr++)
		{
			auto buffer = myCommandBuffers[itr];
			buffer->begin();

			myCommandBufferManager->bindRenderTarget(buffer, myRenderTarget, itr);
			myCommandBufferManager->unbindRenderTarget(buffer);

			buffer->end();
		}

		isInitialized = true;
	}
	
	void DMKRenderer::terminateComponents()
	{
		myCoreObject->idleCall();

		myCommandBufferManager->terminate(myCoreObject, myCommandBuffers);

		myRenderTarget->pSwapChain->terminate(myCoreObject);
		myRenderTarget->pRenderPass->terminate(myCoreObject);
		myRenderTarget->pFrameBuffer->terminate(myCoreObject);

		myCoreObject->terminate();
	}
}
