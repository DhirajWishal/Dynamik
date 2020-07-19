// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Renderer.h"

#include "RUtilities.h"

#include "Core/Math/MathFunctions.h"
#include "Core/Components/RenderableComponents/DebugComponent.h"
#include "Services/RuntimeSystems/AssetRegistry.h"

/* Vulkan headers */
#include "VulkanRBL/VulkanCoreObject.h"
#include "VulkanRBL/Common/VulkanInstance.h"
#include "VulkanRBL/Common/VulkanSurface.h"
#include "VulkanRBL/Common/VulkanDevice.h"
#include "VulkanRBL/Common/VulkanQueue.h"
#include "VulkanRBL/Common/VulkanCommandBuffer.h"
#include "VulkanRBL/Common/VulkanCommandBufferManager.h"
#include "VulkanRBL/Common/VulkanDescriptorSetManager.h"
#include "VulkanRBL/Context/VulkanSwapChain.h"
#include "VulkanRBL/Context/VulkanRenderPass.h"
#include "VulkanRBL/Context/VulkanFrameBuffer.h"
#include "VulkanRBL/Pipelines/VulkanGraphicsPipeline.h"

namespace Dynamik
{
	using namespace Backend;

	/* ---------- CLASS DEFINITION ---------- */
	void DMKRenderer::initialize()
	{
		myCompatibility.isVulkanAvailable = glfwVulkanSupported();

		myAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;

#ifdef DMK_DEBUG
		DMK_INFO("Entered the renderer thread!");

#endif // DMK_DEBUG

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
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_CAMERA:
			initializeCamera(Inherit<RendererInitializeCamera>(myCommand)->pCameraModule);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_GAME_WORLD:
			initializeGameWorld(Inherit<RendererInitializeGameWorld>(myCommand)->pGameWorld);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENVIRONMENT_MAP:
			initializeEnvironmentMap(Inherit<RendererInitializeEnvironmentMap>(myCommand)->pEnvironmentMap);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS:
			initializeFinals();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITY:
			createEntityResources(Inherit<RendererAddEntity>(myCommand)->entity);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITIES:
		{
			auto pEntities = Inherit<RendererInitializeEntities>(myCommand)->pEntities;
			for (auto entity : pEntities)
				createEntityResources(entity);
		}
		break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SUBMIT_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_INITIALIZE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE:
			updateInstruction();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_CAMERA:
			updateCamera();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_ENVIRONMENT:
			updateEnvironment();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_ENTITIES:
			updateEntities();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_BOUNDING_BOXES:
			updateBoundingBoxes();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_SUBMIT:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_FRAME:
			myCoreObject->idleCall();
			isReadyToRun = false;
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_OBJECTS:
			terminateEntities();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE:
			terminateContext();
			terminateComponents();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_UPDATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_SAMPLES:
			setSamples(Inherit<RendererSetSamplesCommand>(myCommand)->samples);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_WINDOW_HANDLE:
			setWindowHandle(Inherit<RendererSetWindowHandleCommand>(myCommand)->windowHandle);
			break;
		case Dynamik::RendererInstruction::RENDERER_RESIZE_FRAME_BUFFER:
			resizeFrameBuffer(Inherit<RendererResizeFrameBuffer>(myCommand)->windowExtent);
			break;
		default:
			break;
		}
	}

	void DMKRenderer::onLoop()
	{
		if (!isReadyToRun)
			return;

		beginFrameInstruction();
		endFrameInstruction();
	}

	void DMKRenderer::onTermination()
	{
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
			myCoreObject = Inherit<RCoreObject>(StaticAllocator<VulkanCoreObject>::rawAllocate().get());
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
			mySwapChain = Inherit<RSwapChain>(StaticAllocator<VulkanSwapChain>::rawAllocate().get());
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
			myRenderTarget.pRenderPass = Inherit<RRenderPass>(StaticAllocator<VulkanRenderPass>::rawAllocate().get());

			/* Attachments: Color, Depth, Swap Chain */
			myRenderTarget.pRenderPass->initialize(myCoreObject, subPasses, { RSubpassDependency() }, mySwapChain);
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

		return myRenderTarget.pRenderPass;
	}

	RFrameBuffer* DMKRenderer::createFrameBuffer()
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			myRenderTarget.pFrameBuffer = Inherit<RFrameBuffer>(StaticAllocator<VulkanFrameBuffer>::rawAllocate().get());
			myRenderTarget.pFrameBuffer->initialize(myCoreObject, myRenderTarget.pRenderPass, mySwapChain, mySwapChain->extent, mySwapChain->bufferCount);
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

		return myRenderTarget.pFrameBuffer;
	}

	void DMKRenderer::createContext(DMKRenderContextType type, DMKViewport viewport)
	{
		myCurrentContextType = type;

		/* Initialize Swap chain */
		createSwapChain(viewport, RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_FIFO);

		/* Initialize Render pass */
		createRenderPass(RUtilities::createSubPasses(myCurrentContextType));

		/* Initialize Frame buffer */
		createFrameBuffer();
	}

	RBuffer* DMKRenderer::createBuffer(const RBufferType& type, UI64 size, RResourceMemoryType memoryType)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			RBuffer* pBuffer = StaticAllocator<VulkanBuffer>::rawAllocate();
			pBuffer->initialize(myCoreObject, type, size, memoryType);

			return pBuffer;
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

	RBuffer* DMKRenderer::createVertexBuffer(UI64 size)
	{
		return createBuffer(RBufferType::BUFFER_TYPE_VERTEX, size, RResourceMemoryType(RESOURCE_MEMORY_TYPE_DEVICE_LOCAL | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	}

	RBuffer* DMKRenderer::createIndexBuffer(UI64 size)
	{
		return createBuffer(RBufferType::BUFFER_TYPE_INDEX, size, RResourceMemoryType(RESOURCE_MEMORY_TYPE_DEVICE_LOCAL | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	}

	void DMKRenderer::copyBuffer(RBuffer* pSrcBuffer, RBuffer* pDstBuffer, UI64 size)
	{
		pDstBuffer->copy(myCoreObject, pSrcBuffer, size, 0, 0);
	}

	void DMKRenderer::copyDataToBuffer(RBuffer* pDstBuffer, VPTR data, UI64 size, UI64 offset)
	{
		auto staggingBuffer = createBuffer(RBufferType::BUFFER_TYPE_STAGGING, size);
		staggingBuffer->setData(myCoreObject, size, offset, data);

		copyBuffer(staggingBuffer, pDstBuffer, size);

		staggingBuffer->terminate(myCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(staggingBuffer, 0);
	}

	RTexture* DMKRenderer::createTexture(const DMKTexture* pTexture)
	{
		switch (myAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_NONE:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			RTexture* texture = Inherit<RTexture>(StaticAllocator<VulkanTexture>::rawAllocate().get());
			texture->initialize(myCoreObject, (DMKTexture*)pTexture);
			texture->createView(myCoreObject);

			if ((pTexture->type == DMKTextureType::TEXTURE_TYPE_CUBEMAP) || (pTexture->type == DMKTextureType::TEXTURE_TYPE_CUBEMAP_ARRAY)) /* TODO */
				texture->createSampler(myCoreObject, RImageSamplerCreateInfo::createCubeMapSampler());
			else
				texture->createSampler(myCoreObject, RImageSamplerCreateInfo::createDefaultSampler());

			texture->makeRenderable(myCoreObject);

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

	void DMKRenderer::initializeCamera(DMKCameraModule* pCameraModule)
	{
		if (!pCameraModule)
			return;

		if (!myCameraComponent)
			myCameraComponent = StaticAllocator<RCameraComponent>::rawAllocate();

		myCameraComponent->pCameraModule = pCameraModule;
		myCameraComponent->pUniformBuffer = createBuffer(RBufferType::BUFFER_TYPE_UNIFORM, sizeof(DMKCameraMatrix));

		DMKCameraMatrix _matrix;
		_matrix.projection = DMKMathFunctions::perspective(DMKMathFunctions::radians(45.0f), mySwapChain->extent.width / mySwapChain->extent.height, 0.001f, 256.0f);
		_matrix.view = DMKMathFunctions::lookAt(pCameraModule->position, pCameraModule->position + pCameraModule->front, pCameraModule->cameraUp);
		myCameraComponent->pUniformBuffer->setData(myCoreObject, sizeof(_matrix), 0, &_matrix);
	}

	void DMKRenderer::initializeEnvironmentMap(DMKEnvironmentMap* pEnvironmentMap)
	{
		if (!pEnvironmentMap)
			return;

		/* Initialize Sky Box */
		myCurrentEnvironment.pMeshComponent = &pEnvironmentMap->skyBox;

		/* Initialize Material */
		{
			if (pEnvironmentMap->skyBox.materials.size() > 1)
				DMK_WARN("Environment Maps only allow one material!");

			for (auto material : myCurrentEnvironment.pMeshComponent->materials)
				for (auto texture : material.textureContainers)
					myCurrentEnvironment.pTexture = createTexture(texture.pTexture);
		}

		/* Initialize Uniforms */
		myCurrentEnvironment.pUniformBuffer = createBuffer(RBufferType::BUFFER_TYPE_UNIFORM, sizeof(MAT4));
		myCurrentEnvironment.pUniformBuffer->setData(myCoreObject, sizeof(MAT4), 0, &pEnvironmentMap->skyBox.modelMatrix);

		/* Initialize Pipeline */
		myCurrentEnvironment.pPipeline = RUtilities::allocatePipeline(myAPI);

		RPipelineSpecification pipelineCreateInfo = {};
		pipelineCreateInfo.shaders = pEnvironmentMap->skyBox.shaderModules;
		pipelineCreateInfo.scissorInfos.resize(1);
		pipelineCreateInfo.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
		pipelineCreateInfo.multiSamplingInfo.sampleCount = myCoreObject->sampleCount;
		pipelineCreateInfo.rasterizerInfo.frontFace = RFrontFace::FRONT_FACE_CLOCKWISE;
		myCurrentEnvironment.pPipeline->initialize(myCoreObject, pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &myRenderTarget, mySwapChain);

		/* Initialize Vertex and Index Buffers */
		if (pEnvironmentMap->skyBox.vertexBuffer.size() || pEnvironmentMap->skyBox.indexBuffer.size())
			myDrawCallManager.addDrawEntry(pEnvironmentMap->skyBox.vertexBuffer, &pEnvironmentMap->skyBox.indexBuffer, myCurrentEnvironment.pPipeline);
		else
			myDrawCallManager.addEmptyEntry(myCurrentEnvironment.pPipeline);

		/* Initialize Pipeline Resources */
		/* Initialize Uniform Buffer Resources */
		ARRAY<RBuffer*> uniformBuffers = { myCurrentEnvironment.pUniformBuffer };

		if (myCameraComponent->pUniformBuffer)
			uniformBuffers.pushBack(myCameraComponent->pUniformBuffer);

		/* Initialize Texture Resources */
		ARRAY<RTexture*> textures = { myCurrentEnvironment.pTexture };

		myCurrentEnvironment.pPipeline->initializeResources(myCoreObject, uniformBuffers, textures);
	}

	void DMKRenderer::createEntityResources(DMKGameEntity* pGameEntity)
	{
		REntity entity;
		for (UI64 index = 0; index < pGameEntity->componentManager.getObjectArray<DMKStaticMeshComponent>()->size(); index++)
		{
			RMeshObject meshComponent;
			meshComponent.pMeshComponent = pGameEntity->componentManager.getObject<DMKStaticMeshComponent>(index);

			/* Initialize Materials */
			for (auto material : meshComponent.pMeshComponent->materials)
			{
				/* Initialize Textures */
				for (auto texture : material.textureContainers)
					meshComponent.pTextures.pushBack(createTexture(texture.pTexture));
			}

			/* Initialize Uniform Buffers */
			{
				/* Initialize Default Uniform */
				RBuffer* defaultUniform = createBuffer(RBufferType::BUFFER_TYPE_UNIFORM, meshComponent.pMeshComponent->getUniformByteSize());
				meshComponent.pUniformBuffer = defaultUniform;

				meshComponent.pUniformBuffer->setData(myCoreObject, sizeof(meshComponent.pMeshComponent->modelMatrix), 0, &meshComponent.pMeshComponent->modelMatrix);
			}

			/* Initialize Pipeline */
			meshComponent.pPipeline = RUtilities::allocatePipeline(myAPI);

			RPipelineSpecification pipelineCreateInfo = {};
			pipelineCreateInfo.shaders = meshComponent.pMeshComponent->shaderModules;
			pipelineCreateInfo.scissorInfos.resize(1);
			pipelineCreateInfo.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
			pipelineCreateInfo.multiSamplingInfo.sampleCount = myCoreObject->sampleCount;
			meshComponent.pPipeline->initialize(myCoreObject, pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &myRenderTarget, mySwapChain);

			/* Initialize Vertex and Index Buffers */
			if (meshComponent.pMeshComponent->vertexBuffer.size() || meshComponent.pMeshComponent->indexBuffer.size())
				meshComponent.resourceIndex = myDrawCallManager.addDrawEntry(meshComponent.pMeshComponent->vertexBuffer, &meshComponent.pMeshComponent->indexBuffer, meshComponent.pPipeline);
			else
				meshComponent.resourceIndex = myDrawCallManager.addEmptyEntry(meshComponent.pPipeline);

			/* Initialize Pipeline Resources */
			{
				/* Initialize Uniform Buffer Resources */
				ARRAY<RBuffer*> uniformBuffers;
				if (meshComponent.pUniformBuffer)
					uniformBuffers.pushBack(meshComponent.pUniformBuffer);

				if (pGameEntity->isCameraAvailable && myCameraComponent->pUniformBuffer)
					uniformBuffers.pushBack(myCameraComponent->pUniformBuffer);

				/* Initialize Texture Resources */
				ARRAY<RTexture*> textures;
				textures.insert(meshComponent.pTextures);

				meshComponent.pPipeline->initializeResources(myCoreObject, uniformBuffers, textures);

				/* Initialize Constant Blocks */
				for (UI64 itr = 0; itr < meshComponent.pMeshComponent->materials.size(); itr++)
				{
					auto& material = meshComponent.pMeshComponent->materials[itr];

					meshComponent.pPipeline->submitConstantData(
						StaticAllocator<DMKMaterial::MaterialPushBlock>::allocateInit(material.generatePushBlock()),
						itr);
				}
			}

			entity.meshObjects.pushBack(meshComponent);
		}

		/* Initialize Attachments */
		{
			/* Initialize Bounding Boxes */
			for (UI64 index = 0; index < pGameEntity->componentManager.getObjectArray<DMKBoundingBoxAttachment>()->size(); index++)
				myBoundingBoxes.pushBack(createBoundingBox(pGameEntity->getComponent<DMKBoundingBoxAttachment>(index)));
		}

		/* Initialize Debug Components */
		for (UI64 index = 0; index < pGameEntity->componentManager.getObjectArray<DMKDebugComponent>()->size(); index++)
		{
			auto debug = pGameEntity->getComponent<DMKDebugComponent>(index);
			RDebugMeshComponent mesh;
			mesh.pComponent = debug;

			/* Initialize Uniforms */
			if (debug->getUniformBuffer().byteSize())
			{
				mesh.pUniformBuffer = RUtilities::allocateBuffer(myAPI);
				mesh.pUniformBuffer->initialize(myCoreObject, RBufferType::BUFFER_TYPE_UNIFORM, debug->getUniformBuffer().byteSize());
				mesh.pUniformBuffer->setData(myCoreObject, debug->getUniformBuffer().byteSize(), 0, debug->uniformBuffer.data());
			}

			/* Initialize Materials */
			for (auto material : debug->getMaterials())
			{
				/* Initialize Textures */
				for (auto texture : material.textureContainers)
					mesh.pTextures.pushBack(createTexture(texture.pTexture));
			}

			/* Initialize Pipeline */
			mesh.pPipeline = RUtilities::allocatePipeline(myAPI);

			RPipelineSpecification pipelineCreateInfo = {};
			pipelineCreateInfo.shaders = debug->shaders;
			pipelineCreateInfo.scissorInfos.resize(1);
			pipelineCreateInfo.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
			pipelineCreateInfo.multiSamplingInfo.sampleCount = myCoreObject->sampleCount;
			pipelineCreateInfo.primitiveAssemblyInfo.primitiveTopology = RPrimitiveTopology::PRIMITIVE_TOPOLOGY_LINE_LIST;
			mesh.pPipeline->initialize(myCoreObject, pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &myRenderTarget, mySwapChain);

			/* Initialize Primitives */
			if (debug->vertexBuffer.size() || debug->indexBuffer.size())
				mesh.resourceIndex = myDrawCallManager.addDebugEntry(debug->vertexBuffer, &debug->indexBuffer, mesh.pPipeline);
			else
				mesh.resourceIndex = myDrawCallManager.addEmptyEntry(mesh.pPipeline);

			/* Initialize Pipeline Resources */
			{
				/* Initialize Uniform Buffer Resources */
				ARRAY<RBuffer*> uniformBuffers;
				if (mesh.pUniformBuffer)
					uniformBuffers.pushBack(mesh.pUniformBuffer);

				if (pGameEntity->isCameraAvailable && myCameraComponent->pUniformBuffer)
					uniformBuffers.pushBack(myCameraComponent->pUniformBuffer);

				/* Initialize Texture Resources */
				ARRAY<RTexture*> textures;
				textures.insert(mesh.pTextures);

				mesh.pPipeline->initializeResources(myCoreObject, uniformBuffers, textures);

				/* Initialize Constant Blocks */
				for (UI64 itr = 0; itr < debug->materials.size(); itr++)
				{
					auto& material = debug->materials[itr];
					mesh.pPipeline->submitConstantData(
						StaticAllocator<DMKMaterial::MaterialPushBlock>::allocateInit(material.generatePushBlock()),
						itr);
				}
			}

			myDebugObjects.pushBack(mesh);
		}

		myEntities.pushBack(entity);
	}

	void DMKRenderer::initializeGameWorld(DMKGameWorld* pGameWorld)
	{
		if (!pGameWorld)
			return;

		/* Initialize Environment Map */
		initializeEnvironmentMap(pGameWorld->pEnvironmentMap);

		/* Initialize Entities */
		for (auto entity : pGameWorld->entities)
			createEntityResources(entity);
	}

	void DMKRenderer::updateResources()
	{
		for (UI64 entityIndex = 0; entityIndex < myEntities.size(); entityIndex++)
		{
			for (UI64 meshIndex = 0; meshIndex < myEntities[entityIndex].meshObjects.size(); meshIndex++)
			{

			}
		}
	}

	void DMKRenderer::bindEnvironment(RCommandBuffer* pCommandBuffer, UI64* pFirstVertex, UI64* pFirstIndex)
	{
		pCommandBuffer->bindGraphicsPipeline(myCurrentEnvironment.pPipeline);
		pCommandBuffer->drawIndexed(*pFirstVertex, myCurrentEnvironment.indexBufferOffset, myCurrentEnvironment.pMeshComponent->indexCount, 1);

		*pFirstIndex += myCurrentEnvironment.pMeshComponent->indexCount;
		*pFirstVertex += myCurrentEnvironment.pMeshComponent->vertexBuffer.size();
	}

	void DMKRenderer::initializeCommandBuffers()
	{
		myCommandBuffers = myCommandBufferManager->allocateCommandBuffers(myCoreObject, mySwapChain->bufferCount);

		for (UI32 itr = 0; itr < myCommandBuffers.size(); itr++)
		{
			myDrawCallManager.setCommandBuffer(myCommandBuffers[itr]);
			myDrawCallManager.beginCommand();
			myDrawCallManager.bindRenderTarget(&myRenderTarget, mySwapChain, itr);

			myDrawCallManager.bindDrawCalls(RDrawCallType::DRAW_CALL_TYPE_INDEX);

			myDrawCallManager.unbindRenderTarget();
			myDrawCallManager.endCommand();
		}

		isReadyToRun = true;
	}

	void DMKRenderer::initializeFinals()
	{
		myDrawCallManager.initializeBuffers(myCoreObject);

		myCommandBufferManager = Inherit<RCommandBufferManager>(StaticAllocator<VulkanCommandBufferManager>::rawAllocate().get());
		myCommandBufferManager->initialize(myCoreObject);

		initializeCommandBuffers();
	}

	void DMKRenderer::resizeFrameBuffer(DMKExtent2D windowExtent)
	{
		isReadyToRun = false;

		/* Reset Command Buffers */
		myCoreObject->idleCall();
		myCommandBufferManager->resetBuffers(myCoreObject, myCommandBuffers);

		/* Terminate The Current Context */
		{
			/* Terminate Frame Buffer */
			myRenderTarget.pFrameBuffer->terminate(myCoreObject);

			/* Terminate Render Pass */
			myRenderTarget.pRenderPass->terminate(myCoreObject);

			/* Terminate Swap Chain */
			mySwapChain->terminate(myCoreObject);
		}

		/* Create New Context */
		{
			/* Initialize View port */
			DMKViewport newViewPort;
			newViewPort.windowHandle = myWindowHandle;
			newViewPort.width = (I32)windowExtent.width;
			newViewPort.height = (I32)windowExtent.height;

			/* Initialize Swap Chain */
			mySwapChain->initialize(myCoreObject, newViewPort, RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_FIFO);

			/* Initialize Render Pass */
			myRenderTarget.pRenderPass->initialize(myCoreObject, RUtilities::createSubPasses(myCurrentContextType), { RSubpassDependency() }, mySwapChain);

			/* Initialize Frame Buffer */
			myRenderTarget.pFrameBuffer->initialize(myCoreObject, myRenderTarget.pRenderPass, mySwapChain, mySwapChain->extent, mySwapChain->bufferCount);
		}

		/* Initialize Pipelines */
		{
			/* Initialize Environment Map Pipeline */
			myCurrentEnvironment.pPipeline->reCreate(myCoreObject, &myRenderTarget, mySwapChain);

			/* Initialize Entity Pipelines */
			for (auto entity : myEntities)
				for (auto mesh : entity.meshObjects)
					mesh.pPipeline->reCreate(myCoreObject, &myRenderTarget, mySwapChain);

			/* Initialize Bounding Boxes */
			for (auto box : myBoundingBoxes)
				box.pPipeline->reCreate(myCoreObject, &myRenderTarget, mySwapChain);

			/* Initialize Debug Objects */
			for (auto debug : myDebugObjects)
				debug.pPipeline->reCreate(myCoreObject, &myRenderTarget, mySwapChain);
		}

		/* Initialize Buffers */
		initializeCommandBuffers();
	}

	void DMKRenderer::beginFrameInstruction()
	{
		currentImageIndex = myCoreObject->prepareFrame(mySwapChain);

		if (currentImageIndex == -1)
			resizeFrameBuffer({ (F32)mySwapChain->viewPort.width, (F32)mySwapChain->viewPort.height });
	}

	void DMKRenderer::updateInstruction()
	{
		updateCamera();
		updateEnvironment();
		updateEntities();
		updateBoundingBoxes();
		updateDebugObjects();
	}

	void DMKRenderer::updateCamera()
	{
		if (myCameraComponent)
			myCameraComponent->pUniformBuffer->setData(myCoreObject, sizeof(DMKCameraMatrix), 0, &myCameraComponent->pCameraModule->matrix);
	}

	void DMKRenderer::updateEnvironment()
	{
		if (myCurrentEnvironment.pUniformBuffer)
			myCurrentEnvironment.pUniformBuffer->setData(myCoreObject, sizeof(myCurrentEnvironment.pMeshComponent->getMatrix()), 0, &myCurrentEnvironment.pMeshComponent->modelMatrix);
	}

	void DMKRenderer::updateEntities()
	{
		for (UI64 entityIndex = 0; entityIndex < myEntities.size(); entityIndex++)
		{
			for (UI64 meshIndex = 0; meshIndex < myEntities[entityIndex].meshObjects.size(); meshIndex++)
			{
				if (myEntities[entityIndex].meshObjects[meshIndex].pMeshComponent->isUpdated())
				{
					myEntities[entityIndex].meshObjects[meshIndex].pUniformBuffer->setData(myCoreObject, sizeof(MAT4), 0, &myEntities[entityIndex].meshObjects[meshIndex].pMeshComponent->modelMatrix);
					myEntities[entityIndex].meshObjects[meshIndex].pMeshComponent->resetUpdateNotice();
				}
			}
		}
	}

	void DMKRenderer::updateBoundingBoxes()
	{
		for (auto boundingBox : myBoundingBoxes)
			boundingBox.pUniformBuffer->setData(myCoreObject, boundingBox.pBoundingBox->getUniform().byteSize(), 0, boundingBox.pBoundingBox->getUniform().data());
	}

	void DMKRenderer::updateDebugObjects()
	{
		for (auto debug : myDebugObjects)
		{
			/* Update Vertex Data */
			auto entry = myDrawCallManager.getDebugEntry(debug.resourceIndex);
			entry.pVertexBuffer->setData(myCoreObject, debug.pComponent->getVertexBuffer().byteSize(), 0, debug.pComponent->getVertexBuffer().data());
		}
	}

	void DMKRenderer::endFrameInstruction()
	{
		myCoreObject->submitCommand(myCommandBuffers[currentImageIndex], mySwapChain);
	}

	void DMKRenderer::terminateContext()
	{
		/* Terminate Frame Buffer */
		myRenderTarget.pFrameBuffer->terminate(myCoreObject);
		StaticAllocator<RFrameBuffer>::rawDeallocate(myRenderTarget.pFrameBuffer, 0);

		/* Terminate Render Pass */
		myRenderTarget.pRenderPass->terminate(myCoreObject);
		StaticAllocator<RRenderPass>::rawDeallocate(myRenderTarget.pRenderPass, 0);

		/* Terminate Swap Chain */
		mySwapChain->terminate(myCoreObject);
		StaticAllocator<RSwapChain>::rawDeallocate(mySwapChain, 0);
	}

	void DMKRenderer::terminateComponents()
	{
		/* Terminate Vertex and Index Buffers */
		myDrawCallManager.terminate(myCoreObject);

		/* Terminate Command Buffers */
		myCommandBufferManager->terminate(myCoreObject, myCommandBuffers);
		StaticAllocator<RCommandBufferManager>::rawDeallocate(myCommandBufferManager, 0);

		/* Terminate Core Object */
		myCoreObject->terminate();
		StaticAllocator<RCoreObject>::rawDeallocate(myCoreObject, 0);
	}

	void DMKRenderer::terminateEntities()
	{
		/* Terminate Camera */
		if (myCameraComponent)
		{
			myCameraComponent->pUniformBuffer->terminate(myCoreObject);
			StaticAllocator<RBuffer>::rawDeallocate(myCameraComponent->pUniformBuffer, 0);
		}

		/* Terminate Environment Map */
		{
			if (myCurrentEnvironment.pPipeline)
			{
				myCurrentEnvironment.pPipeline->terminate(myCoreObject);
				StaticAllocator<RPipelineObject>::rawDeallocate(myCurrentEnvironment.pPipeline, 0);
			}

			if (myCurrentEnvironment.pTexture)
			{
				myCurrentEnvironment.pTexture->terminate(myCoreObject);
				StaticAllocator<RTexture>::rawDeallocate(myCurrentEnvironment.pTexture, 0);
			}

			if (myCurrentEnvironment.pUniformBuffer)
			{
				myCurrentEnvironment.pUniformBuffer->terminate(myCoreObject);
				StaticAllocator<RBuffer>::rawDeallocate(myCurrentEnvironment.pUniformBuffer, 0);
			}
		}

		/* Terminate Entities */
		for (auto entity : myEntities)
		{
			for (auto mesh : entity.meshObjects)
			{
				for (auto texture : mesh.pTextures)
				{
					texture->terminate(myCoreObject);
					StaticAllocator<RTexture>::rawDeallocate(texture, 0);
				}

				if (mesh.pUniformBuffer)
				{
					mesh.pUniformBuffer->terminate(myCoreObject);
					StaticAllocator<RBuffer>::rawDeallocate(mesh.pUniformBuffer, 0);
				}

				if (mesh.pPipeline)
				{
					mesh.pPipeline->terminate(myCoreObject);

					for (auto block : mesh.pPipeline->constantBlocks)
						StaticAllocator<BYTE>::rawDeallocate(block.data, block.byteSize);

					StaticAllocator<RPipelineObject>::rawDeallocate(mesh.pPipeline, 0);
				}
			}

			entity.meshObjects.clear();
		}

		myEntities.clear();

		/* Terminate Bounding Boxes */
		for (auto boundingBox : myBoundingBoxes)
			boundingBox.terminate(myCoreObject);

		myBoundingBoxes.clear();

		/* Terminate Debug Objects */
		for (auto debug : myDebugObjects)
		{
			if (debug.pPipeline)
			{
				debug.pPipeline->terminate(myCoreObject);
				StaticAllocator<RPipelineObject>::rawDeallocate(debug.pPipeline, 0);
			}

			if (debug.pUniformBuffer)
			{
				debug.pUniformBuffer->terminate(myCoreObject);
				StaticAllocator<RBuffer>::rawDeallocate(debug.pUniformBuffer, 0);
			}
		}

		myDebugObjects.clear();
	}

	RBoundingBox DMKRenderer::createBoundingBox(DMKBoundingBoxAttachment* pBoundingBox)
	{
		RBoundingBox boundingBox(myAPI);
		boundingBox.pBoundingBox = pBoundingBox;

		if (myCameraComponent->pUniformBuffer)
			boundingBox.initialize(myCoreObject, &myRenderTarget, mySwapChain, myCameraComponent->pUniformBuffer);
		else
			boundingBox.initialize(myCoreObject, &myRenderTarget, mySwapChain, nullptr);

		if (pBoundingBox->vertexBuffer.size() || pBoundingBox->indexBuffer.size())
			myDrawCallManager.addDrawEntry(pBoundingBox->vertexBuffer, &pBoundingBox->indexBuffer, boundingBox.pPipeline);
		else
			myDrawCallManager.addEmptyEntry(boundingBox.pPipeline);

		return boundingBox;
	}
}
