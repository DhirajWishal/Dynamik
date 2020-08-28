// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Renderer.h"

#include "RUtilities.h"

#include "Core/Math/MathFunctions.h"
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
#include "VulkanRBL/Lighting/VulkanBRDFTable.h"
#include "VulkanRBL/Lighting/VulkanPreFilteredCube.h"
#include "VulkanRBL/Lighting/VulkanIrradianceCube.h"
#include "VulkanRBL/Clients/VulkanImGuiBackend.h"

#include "Managers/Thread/ThreadFunction.inl"

#define DMK_BUILD_STUDIO

using namespace Backend;

/* ---------- CLASS DEFINITION ---------- */
void DMKRenderer::processCommand(STRING commandName)
{
	if (commandName == typeid(DMKRendererCommand).name())
	{
		auto instruction = pCommandService->getCommand<DMKRendererCommand>().instruction;

		switch (instruction)
		{
		case RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE:

#ifdef DMK_DEBUG
			myCoreObject = createCore(true);

#else
			myCoreObject = createCore(false);

#endif // DMK_DEBUG
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS:
			initializeFinals();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_SUBMIT_OBJECTS:
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_DRAW_INITIALIZE:
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE:
			if (!isReadyToRun)
				return;

			beginFrameInstruction();
			updateInstruction();
			endFrameInstruction();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_ENVIRONMENT:
			updateEnvironment();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_ENTITIES:
			updateEntities();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE_BOUNDING_BOXES:
			updateBoundingBoxes();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_DRAW_SUBMIT:
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_FRAME:
			myCoreObject->idleCall();
			isReadyToRun = false;
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_OBJECTS:
			terminateEntities();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_TERMINATE:
			terminateContext();
			terminateComponents();
			break;
		case RendererInstruction::RENDERER_INSTRUCTION_UPDATE_OBJECTS:
			break;
		case RendererInstruction::RENDERER_SET_IM_GUI_CONTEXT:
			break;
		case RendererInstruction::RENDERER_UPDATE_IM_GUI:
			myImGuiBackend->updateResources();
			break;
		default:
			DMK_ERROR("Unsupported command!");
			break;
		}
	}

	else if (commandName == typeid(RendererSetSamplesCommand).name())
		setSamples(pCommandService->getCommand<RendererSetSamplesCommand>().samples);

	else if (commandName == typeid(RendererSetWindowHandleCommand).name())
		setWindowHandle(pCommandService->getCommand<RendererSetWindowHandleCommand>().windowHandle);

	else if (commandName == typeid(RendererCreateContextCommand).name())
	{
		auto command = pCommandService->getCommand<RendererCreateContextCommand>();
		createContext(command.contextType, command.viewport);
	}

	else if (commandName == typeid(RendererInitializeEnvironmentEntity).name())
	{
		auto command = pCommandService->getCommand<RendererInitializeEnvironmentEntity>();
		initializeEnvironmentEntity(command.pEnvironmentEntity, command.pProgressMeter);
	}

	else if (commandName == typeid(RendererSubmitStaticEntity).name())
	{
		auto command = pCommandService->getCommand<RendererSubmitStaticEntity>();
		createStaticModelEntityResources(command.pEntity, command.pProgressMeter);
	}

	else if (commandName == typeid(RendererSubmitAnimatedEntity).name())
	{
		auto command = pCommandService->getCommand<RendererSubmitAnimatedEntity>();
		createAnimatedModelEntityResources(command.pEntity, command.pProgressMeter);
	}

	else if (commandName == typeid(RendererRemoveStaticModelEntity).name())
		removeStaticModelEntityResources(pCommandService->getCommand<RendererRemoveStaticModelEntity>().pStaticModelEntity);

	else if (commandName == typeid(RendererResizeFrameBuffer).name())
		resizeFrameBuffer(pCommandService->getCommand<RendererResizeFrameBuffer>().windowExtent);

	else if (commandName == typeid(RendererCreateImGuiClient).name())
		initializeImGuiClient(pCommandService->getCommand<RendererCreateImGuiClient>().pReturnAddressSpace);

	else if (commandName == typeid(RendererSetImGuiContext).name())
	{
		if (myImGuiBackend)
			myImGuiBackend->setContext(pCommandService->getCommand<RendererSetImGuiContext>().pContext);
	}
}

void DMKRenderer::onLoop()
{
	if (!isReadyToRun)
		return;

	beginFrameInstruction();
	myDrawCallManager.update(&myRenderTarget, mySwapChain, currentImageIndex);

	/* Update the Im Gui client */
	if (myImGuiBackend)
		myImGuiBackend->onRendererUpdate(currentImageIndex, mySwapChain, myDrawCallManager.getPrimaryCommandBuffer(currentImageIndex));

	endFrameInstruction();
}

void DMKRenderer::onTermination()
{
	myCoreObject->idleCall();

	terminateEntities();
	terminateContext();
	terminateComponents();

	DMK_INFO("Terminated the renderer thread!");
}

void DMKRenderer::terminateThread()
{
	pCommandService->issueControlCommand(DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_TERMINATE);
}

void DMKRenderer::initializeInternals()
{
	myCompatibility.isVulkanAvailable = glfwVulkanSupported();

	myAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;

#ifdef DMK_DEBUG
	DMK_INFO("Entered the renderer thread!");

#endif // DMK_DEBUG
}

void DMKRenderer::terminateInternals()
{
	StaticAllocator<DMKThreadCommandService>::rawDeallocate(pCommandService);
}

void DMKRenderer::issueRawCommand(RendererInstruction instruction)
{
	pCommandService->issueCommand<DMKRendererCommand>(DMKRendererCommand(instruction));
}

void DMKRenderer::initializeCMD()
{
	issueRawCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE);
}

void DMKRenderer::initializeFinalsCMD()
{
	issueRawCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS);
}

void DMKRenderer::setSamplesCMD(DMKSampleCount samples)
{
	RendererSetSamplesCommand _command;
	_command.samples = samples;

	pCommandService->issueCommand<RendererSetSamplesCommand>(_command);
}

void DMKRenderer::setWindowHandleCMD(DMKWindowHandle* pWindowHandle)
{
	RendererSetWindowHandleCommand _command;
	_command.windowHandle = pWindowHandle;

	pCommandService->issueCommand<RendererSetWindowHandleCommand>(_command);
}

void DMKRenderer::createContextCMD(DMKViewport viewPort, DMKRenderContextType contextType)
{
	RendererCreateContextCommand _command;
	_command.viewport = viewPort;
	_command.contextType = contextType;

	pCommandService->issueCommand<RendererCreateContextCommand>(_command);
}

void DMKRenderer::setImGuiContextCMD(ImGuiContext* pContext)
{
	RendererSetImGuiContext _command;
	_command.pContext = pContext;

	pCommandService->issueCommand<RendererSetImGuiContext>(_command);
}

void DMKRenderer::initializeEnvironmentEntityCMD(DMKEnvironmentEntity* pEnvironmentEntity, UI32* pProgressMeter)
{
	if (!pEnvironmentEntity->isInitializedEnvironmentEntity)
	{
		pEnvironmentEntity->onInitializeEnvironment();
		pEnvironmentEntity->isInitializedEnvironmentEntity = true;
	}

	RendererInitializeEnvironmentEntity _command;
	_command.pEnvironmentEntity = pEnvironmentEntity;
	_command.pProgressMeter = pProgressMeter;

	pCommandService->issueCommand<RendererInitializeEnvironmentEntity>(_command);
}

void DMKRenderer::submitStaticModelEntityCMD(DMKStaticModelEntity* pStaticModelEntity, UI32* pProgressMeter)
{
	if (!pStaticModelEntity->isInitializedStaticModel)
	{
		pStaticModelEntity->onInitializeStaticEntity();
		pStaticModelEntity->isInitializedStaticModel = true;
	}

	RendererSubmitStaticEntity _command;
	_command.pEntity = pStaticModelEntity;
	_command.pProgressMeter = pProgressMeter;

	pCommandService->issueCommand<RendererSubmitStaticEntity>(_command);
}

void DMKRenderer::submitAnimatedModelEntityCMD(DMKAnimatedModelEntity* pAnimatedModelEntity, UI32* pProgressMeter)
{
	if (!pAnimatedModelEntity->isInitializedAnimatedEntity)
	{
		pAnimatedModelEntity->onInitializeAnimatedEntity();
		pAnimatedModelEntity->isInitializedAnimatedEntity = true;
	}

	RendererSubmitAnimatedEntity _command;
	_command.pEntity = pAnimatedModelEntity;
	_command.pProgressMeter = pProgressMeter;

	pCommandService->issueCommand<RendererSubmitAnimatedEntity>(_command);
}

void DMKRenderer::removeStaticModelEntityCMD(DMKStaticModelEntity* pStaticModelEntity)
{
	RendererRemoveStaticModelEntity _command;
	_command.pStaticModelEntity = pStaticModelEntity;

	pCommandService->issueCommand<RendererRemoveStaticModelEntity>(_command);
}

void DMKRenderer::removeAnimatedModelEntityCMD(DMKAnimatedModelEntity* pAnimatedModelEntity)
{
}

void DMKRenderer::removeEnvironmentMapEntityCMD(DMKEnvironmentEntity* pEnvironmentMapEntity)
{
}

void DMKRenderer::setFrameBufferResizeCMD(DMKExtent2D newExtent)
{
	RendererResizeFrameBuffer _command;
	_command.windowExtent = newExtent;

	pCommandService->issueCommand<RendererResizeFrameBuffer>(_command);
}

void DMKRenderer::createImGuiClientCMD(DMKImGuiBackendHandle** returnAddressSpace)
{
	RendererCreateImGuiClient _command;
	_command.pReturnAddressSpace = returnAddressSpace;

	pCommandService->issueCommand<RendererCreateImGuiClient>(_command);
}

void DMKRenderer::submitPrimitiveCMD(DMKMeshObject* pMeshObject)
{
}

void DMKRenderer::submitPrimitivesCMD(ARRAY<DMKMeshObject*> pMeshObjects)
{
}

void DMKRenderer::initializeThread()
{
	pCommandService = StaticAllocator<DMKThreadCommandService>::rawAllocate();

	pThread = StaticAllocator<std::thread>::allocate();
	pThread->swap(std::thread(basicThreadFunction<DMKRenderer>, pCommandService));
}

void DMKRenderer::onInitialize()
{
	initializeInternals();
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
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
	{
		myCoreObject = Inherit<RCoreObject>(StaticAllocator<VulkanCoreObject>::rawAllocate().get());
		myCoreObject->initialize(myWindowHandle, mySampleCount, bEnableValidation);
	}
	break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
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
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
	{
		mySwapChain = Inherit<RSwapChain>(StaticAllocator<VulkanSwapChain>::rawAllocate().get());
		mySwapChain->initialize(myCoreObject, viewport, presentMode);
	}
	break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		DMK_ERROR_BOX("Invalid rendering API!");
		break;
	}

	return mySwapChain;
}

RRenderPass* DMKRenderer::createRenderPass(ARRAY<RSubpassAttachment> subPasses)
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
	{
		myRenderTarget.pRenderPass = Inherit<RRenderPass>(StaticAllocator<VulkanRenderPass>::rawAllocate().get());

		/* Attachments: Color, Depth, Swap Chain */
		myRenderTarget.pRenderPass->initialize(myCoreObject, subPasses, { RSubpassDependency() }, mySwapChain);
	}
	break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
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
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
	{
		myRenderTarget.pFrameBuffer = Inherit<RFrameBuffer>(StaticAllocator<VulkanFrameBuffer>::rawAllocate().get());
		myRenderTarget.pFrameBuffer->initialize(myCoreObject, myRenderTarget.pRenderPass, mySwapChain->extent, mySwapChain->bufferCount, RUtilities::getFrameBufferAttachments(myAPI, myRenderTarget.pRenderPass->subPasses, myCoreObject, mySwapChain, mySwapChain->extent));
	}
	break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
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
	createRenderPass(RUtilities::createSubPasses(myCurrentContextType, myCoreObject, mySwapChain));

	/* Initialize Frame buffer */
	createFrameBuffer();
}

RBuffer* DMKRenderer::createBuffer(const RBufferType& type, UI64 size, RResourceMemoryType memoryType)
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
	{
		RBuffer* pBuffer = StaticAllocator<VulkanBuffer>::rawAllocate();
		pBuffer->initialize(myCoreObject, type, size, memoryType);

		return pBuffer;
	}
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
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
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
	{
		RTexture* texture = Inherit<RTexture>(StaticAllocator<VulkanTexture>::rawAllocate().get());
		texture->initialize(myCoreObject, Cast<DMKTexture*>(pTexture));
		texture->createView(myCoreObject);

		if ((pTexture->type == DMKTextureType::TEXTURE_TYPE_CUBEMAP) || (pTexture->type == DMKTextureType::TEXTURE_TYPE_CUBEMAP_ARRAY)) /* TODO */
			texture->createSampler(myCoreObject, RImageSamplerCreateInfo::createCubeMapSampler(0.0f));
		else
			texture->createSampler(myCoreObject, RImageSamplerCreateInfo::createDefaultSampler(0.0f));
		return texture;
	}
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}

RBRDFTable* DMKRenderer::createBRDFTable()
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanBRDFTable>::rawAllocate();
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}

RIrradianceCube* DMKRenderer::createIrradianceCube()
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanIrradianceCube>::rawAllocate();
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}

RPreFilteredCube* DMKRenderer::createPreFilteredCube()
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanPreFilteredCube>::rawAllocate();
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}

RImGuiBackend* DMKRenderer::allocateImGuiClient()
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanImGuiBackend>::rawAllocate();
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}

void DMKRenderer::initializeEnvironmentEntity(DMKEnvironmentEntity* pEnvironmentEntity, UI32* pProgressMeter)
{
#define INC_PROGRESS if(pProgressMeter) (*pProgressMeter)++

	if (!pEnvironmentEntity)
		return;

	INC_PROGRESS;

	RMeshObject renderMesh = {};

	/* Initialize Sky Box */
	myCurrentEnvironment.pParentEntity = pEnvironmentEntity;

	/* Initialize Material */
	{
		if (pEnvironmentEntity->skyBoxMesh.getMaterial().textureContainers.size() > 1)
			DMK_WARN("Environment Maps only allow one material!");
		INC_PROGRESS;

		for (auto texture : pEnvironmentEntity->skyBoxMesh.getMaterial().textureContainers)
			myCurrentEnvironment.pTexture = createTexture(texture.pTexture);
		INC_PROGRESS;
	}

	/* Initialize Vertex Buffer */
	myCurrentEnvironment.renderEntity.pVertexBuffer = createVertexBuffer(pEnvironmentEntity->skyBoxMesh.getVertexBuffer().byteSize());
	myCurrentEnvironment.renderEntity.pVertexBuffer->setData(myCoreObject, pEnvironmentEntity->skyBoxMesh.getVertexBuffer().byteSize(), 0, pEnvironmentEntity->skyBoxMesh.getVertexBuffer().data());
	renderMesh.vertexCount = pEnvironmentEntity->skyBoxMesh.vertexBuffer.size();
	INC_PROGRESS;

	/* Initialize Index Buffer */
	myCurrentEnvironment.renderEntity.pIndexBuffer = createIndexBuffer(pEnvironmentEntity->skyBoxMesh.getIndexBuffer().byteSize());
	myCurrentEnvironment.renderEntity.pIndexBuffer->setData(myCoreObject, pEnvironmentEntity->skyBoxMesh.getIndexBuffer().byteSize(), 0, pEnvironmentEntity->skyBoxMesh.getIndexBuffer().data());
	renderMesh.indexCount = pEnvironmentEntity->skyBoxMesh.indexBuffer.size();
	INC_PROGRESS;

	/* Initialize Uniforms */
	ARRAY<RBuffer*> uniformBuffers;
	for (auto shaders : pEnvironmentEntity->shaders)
	{
		for (UI64 index = 0; index < shaders.getUniforms().size(); index++)
		{
			RUniformContainer _container;
			_container.pParent = &shaders.getUniform(index);
			_container.pUniformBuffer = createBuffer(RBufferType::BUFFER_TYPE_UNIFORM, _container.pParent->byteSize());
			_container.pUniformBuffer->setData(myCoreObject, _container.pParent->byteSize(), 0, _container.pParent->data());

			uniformBuffers.pushBack(_container.pUniformBuffer);
			myCurrentEnvironment.uniformBuffers.pushBack(_container);

			INC_PROGRESS;
		}
	}

	/* Initialize Pipeline */
	myCurrentEnvironment.renderEntity.pPipelineObject = RUtilities::allocatePipeline(myAPI);

	RPipelineSpecification pipelineCreateInfo = {};
	pipelineCreateInfo.resourceCount = 1;
	pipelineCreateInfo.shaders = pEnvironmentEntity->shaders;
	pipelineCreateInfo.scissorInfos.resize(1);
	pipelineCreateInfo.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
	pipelineCreateInfo.multiSamplingInfo.sampleCount = myCoreObject->sampleCount;
	pipelineCreateInfo.rasterizerInfo.frontFace = RFrontFace::FRONT_FACE_CLOCKWISE;
	myCurrentEnvironment.renderEntity.pPipelineObject->initialize(myCoreObject, pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &myRenderTarget, mySwapChain->viewPort);
	INC_PROGRESS;

	/* Initialize Resources */
	{
		Vector2F dim = { 512.0f, 512.0f };

		/* Initialize the BRDF table */
		myCurrentEnvironment.pBRDFTable = createBRDFTable();
		myCurrentEnvironment.pBRDFTable->initialize(myCoreObject, dim);
		INC_PROGRESS;

		/* Initialize the irradiance cube */
		myCurrentEnvironment.pIrradianceCube = createIrradianceCube();
		myCurrentEnvironment.pIrradianceCube->initialize(myCoreObject, &myCurrentEnvironment, dim);
		INC_PROGRESS;

		/* Initialize the pre filtered cube */
		myCurrentEnvironment.pPreFilteredCube = createPreFilteredCube();
		myCurrentEnvironment.pPreFilteredCube->initialize(myCoreObject, &myCurrentEnvironment, dim);
	}
	INC_PROGRESS;

	/* Initialize Texture Resources */
	ARRAY<RTexture*> textures = { myCurrentEnvironment.pTexture };

	/* Initialize Pipeline Resources */
	renderMesh.pResourceObject = myCurrentEnvironment.renderEntity.pPipelineObject->allocateResources(myCoreObject)[0];
	renderMesh.pResourceObject->update(myCoreObject, uniformBuffers, textures);
	INC_PROGRESS;

	myCurrentEnvironment.renderEntity.meshObjects.pushBack(renderMesh);

	/* Initialize Vertex and Index Buffers */
	myDrawCallManager.addRenderEntity(&myCurrentEnvironment.renderEntity);
	INC_PROGRESS;
}

void DMKRenderer::createStaticModelEntityResources(DMKStaticModelEntity* pEntity, UI32* pProgressMeter)
{
#define INC_PROGRESS if(pProgressMeter) (*pProgressMeter)++

	REntity* pRenderEntity = StaticAllocator<REntity>::rawAllocate();

	pRenderEntity->pPipelineObject = RUtilities::allocatePipeline(myAPI);

	RPipelineSpecification pipelineCreateInfo = {};
	pipelineCreateInfo.resourceCount = pEntity->meshObjects.size();
	pipelineCreateInfo.pPipelineCache = &pRenderEntity->pipelineCache;
	pipelineCreateInfo.shaders = pEntity->shaders;
	pipelineCreateInfo.scissorInfos.resize(1);
	pipelineCreateInfo.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
	pipelineCreateInfo.multiSamplingInfo.sampleCount = myCoreObject->sampleCount;
	pRenderEntity->pPipelineObject->initialize(myCoreObject, pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &myRenderTarget, mySwapChain->viewPort);
	INC_PROGRESS;

	auto resources = pRenderEntity->pPipelineObject->allocateResources(myCoreObject);

	ARRAY<RBuffer*> pUniformBuffers;
	{
		/* Initialize Default Uniform */
		for (auto shader : pEntity->shaders)
		{
			auto UBOs = shader.getUniforms();
			for (UI64 index = 0; index < shader.getUniforms().size(); index++)
			{
				RUniformContainer _container;
				_container.pParent = Cast<DMKUniformBuffer*>(shader.getUniforms().location(index));
				_container.pUniformBuffer = createBuffer(RBufferType::BUFFER_TYPE_UNIFORM, _container.pParent->byteSize());
				_container.pUniformBuffer->setData(myCoreObject, _container.pParent->byteSize(), 0, _container.pParent->data());

				pRenderEntity->uniformContainers.pushBack(_container);
				pUniformBuffers.pushBack(_container.pUniformBuffer);

				INC_PROGRESS;
			}
		}
	}

	UI64 vertexBufferSize = 0;
	UI64 indexBufferSize = 0;

	for (UI32 index = 0; index < pEntity->meshObjects.size(); index++)
	{
		auto pMeshObject = pEntity->meshObjects.location(index);
		auto rMeshObject = createMeshObject(pEntity, pMeshObject, resources[index], pRenderEntity->pPipelineObject, pUniformBuffers, index);
		rMeshObject.vertexOffset = vertexBufferSize / pMeshObject->getVertexBuffer().getLayout().getVertexSize();
		rMeshObject.indexOffset = indexBufferSize / pMeshObject->getIndexBuffer().getIndexSize();

		pRenderEntity->meshObjects.pushBack(rMeshObject);

		vertexBufferSize += pMeshObject->getVertexBuffer().byteSize();
		indexBufferSize += pMeshObject->getIndexBuffer().byteSize();
	}

	/* Initialize Vertex and Index buffers */
	{
		/* Initialize vertex buffer */
		{
			pRenderEntity->pVertexBuffer = createVertexBuffer(vertexBufferSize);
			POINTER<BYTE> vertexPtr = pRenderEntity->pVertexBuffer->getData(myCoreObject, vertexBufferSize, 0);

			for (auto rMeshObject : pRenderEntity->meshObjects)
			{
				DMKMemoryFunctions::copyData(vertexPtr.get(), rMeshObject.pParentObject->getVertexBuffer().data(), rMeshObject.pParentObject->getVertexBuffer().byteSize());
				vertexPtr += rMeshObject.pParentObject->getVertexBuffer().byteSize();
			}

			pRenderEntity->pVertexBuffer->flushMemory(myCoreObject);
		}
		INC_PROGRESS;

		/* initialize index buffer */
		{
			pRenderEntity->pIndexBuffer = createIndexBuffer(indexBufferSize);
			POINTER<BYTE> indexPtr = pRenderEntity->pIndexBuffer->getData(myCoreObject, indexBufferSize, 0);

			for (auto rMeshObject : pRenderEntity->meshObjects)
			{
				DMKMemoryFunctions::copyData(indexPtr.get(), rMeshObject.pParentObject->getIndexBuffer().data(), rMeshObject.pParentObject->getIndexBuffer().byteSize());
				indexPtr += rMeshObject.pParentObject->getIndexBuffer().byteSize();
			}

			pRenderEntity->pIndexBuffer->flushMemory(myCoreObject);
		}
		INC_PROGRESS;
	}

	myEntities.pushBack(pRenderEntity);
	myDrawCallManager.addRenderEntity(pRenderEntity);

	pStaticEntities.pushBack(pEntity);

	pEntity->renderDataID = GetPointerAsInteger(pRenderEntity);

	INC_PROGRESS;
}

void DMKRenderer::createAnimatedModelEntityResources(DMKAnimatedModelEntity* pEntity, UI32* pProgressMeter)
{
}

void DMKRenderer::removeStaticModelEntityResources(DMKStaticModelEntity* pStaticModelEntity)
{
	myCoreObject->idleCall();

	/* Find the required static model from the array and remove it. */
	for (UI64 index = 0; index < pStaticEntities.size(); index++)
	{
		if (pStaticEntities[index] == pStaticModelEntity)
		{
			pStaticModelEntity->onTerminateStaticEntity();
			pStaticEntities.remove(index);
			break;
		}
	}

	/* Find the entity resources from the created entities to terminate and deallocate. */
	for (UI64 index = 0; index < myEntities.size(); index++)
	{
		if (myEntities[index] == ((VPTR)pStaticModelEntity->renderDataID))
		{
			myDrawCallManager.removeRenderEntity(myEntities[index]);
			terminateEntity(myEntities[index]);
			myEntities.remove(index);
			break;
		}
	}

	/* Reset command buffers */
	myDrawCallManager.resetPrimaryCommandBuffers(myCoreObject);
	myDrawCallManager.resetSecondaryCommandBuffers(myCoreObject);

	myDrawCallManager.reCreateBuffers(myCoreObject, &myRenderTarget, mySwapChain, myAPI);
}

void DMKRenderer::removeAnimatedModelEntityResources(DMKAnimatedModelEntity* pAnimatedModelEntity)
{
}

void DMKRenderer::removeEnvironmentMapEntityResources(DMKEnvironmentEntity* pEnvironmentEntity)
{
}

void DMKRenderer::updateResources()
{
	for (UI64 entityIndex = 0; entityIndex < myEntities.size(); entityIndex++)
	{
		for (UI64 meshIndex = 0; meshIndex < myEntities[entityIndex]->meshObjects.size(); meshIndex++)
		{

		}
	}
}

void DMKRenderer::initializeCommandBuffers()
{
	myDrawCallManager.initializeCommandBuffers(myCoreObject, &myRenderTarget, mySwapChain, myAPI);
	isReadyToRun = true;
}

void DMKRenderer::initializeFinals()
{
	initializeCommandBuffers();
}

void DMKRenderer::resizeFrameBuffer(DMKExtent2D windowExtent)
{
	isReadyToRun = false;

	/* Reset Command Buffers */
	myCoreObject->idleCall();
	myDrawCallManager.resetPrimaryCommandBuffers(myCoreObject);

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
		myRenderTarget.pRenderPass->initialize(myCoreObject, RUtilities::createSubPasses(myCurrentContextType, myCoreObject, mySwapChain), { RSubpassDependency() }, mySwapChain);

		/* Initialize Frame Buffer */
		myRenderTarget.pFrameBuffer->initialize(myCoreObject, myRenderTarget.pRenderPass, mySwapChain->extent, mySwapChain->bufferCount, RUtilities::getFrameBufferAttachments(myAPI, myRenderTarget.pRenderPass->subPasses, myCoreObject, mySwapChain, mySwapChain->extent));
	}

	/* Initialize Pipelines */
	{
		/* Initialize Environment Map Pipeline */
		if (myCurrentEnvironment.renderEntity.pPipelineObject)
			myCurrentEnvironment.renderEntity.pPipelineObject->reCreate(myCoreObject, &myRenderTarget, mySwapChain->viewPort);

		/* Initialize Entity Pipelines */
		for (auto entity : myEntities)
			entity->pPipelineObject->reCreate(myCoreObject, &myRenderTarget, mySwapChain->viewPort);

		/* Initialize Bounding Boxes */
		for (auto box : myBoundingBoxes)
			box.pPipeline->reCreate(myCoreObject, &myRenderTarget, mySwapChain->viewPort);
	}

	/* Recreate Im Gui Backend Pipeline. */
	if (myImGuiBackend)
		myImGuiBackend->reCreatePipeline(&myRenderTarget, mySwapChain->viewPort);

	/* Initialize Buffers */
	myDrawCallManager.reCreateBuffers(myCoreObject, &myRenderTarget, mySwapChain, myAPI);

	isReadyToRun = true;
}

void DMKRenderer::beginFrameInstruction()
{
	isPresenting = true;

	currentImageIndex = myCoreObject->prepareFrame(mySwapChain);

	if (currentImageIndex == -1)
	{
		resizeFrameBuffer({ (F32)mySwapChain->viewPort.width, (F32)mySwapChain->viewPort.height });
		beginFrameInstruction();
	}
}

void DMKRenderer::updateInstruction()
{
	updateEnvironment();
	updateEntities();
	updateBoundingBoxes();
	updateDebugObjects();
}

void DMKRenderer::updateEnvironment()
{
	for (auto pUniform : myCurrentEnvironment.uniformBuffers)
		pUniform.pUniformBuffer->setData(myCoreObject, pUniform.pParent->byteSize(), 0, pUniform.pParent->data());
}

void DMKRenderer::updateEntities()
{
	/* Update the current environment map */
	if (myCurrentEnvironment.pParentEntity)
		myCurrentEnvironment.pParentEntity->onUpdateEnvironment();

	/* Update static entities. */
	for (UI64 index = 0; index < pStaticEntities.size(); index++)
		pStaticEntities[index]->onUpdateStaticEntity();

	/* Update animated entities. */
	for (UI64 index = 0; index < pAnimatedEntities.size(); index++)
		pAnimatedEntities[index]->onUpdateAnimatedEntity();

	/* Submit uniform data */
	submitUniformData();
}

void DMKRenderer::updateBoundingBoxes()
{
	//for (auto boundingBox : myBoundingBoxes)
	//	boundingBox.pUniformBuffer->setData(myCoreObject, boundingBox.pBoundingBox->getUniform().byteSize(), 0, boundingBox.pBoundingBox->getUniform().data());
}

void DMKRenderer::updateDebugObjects()
{
}

void DMKRenderer::endFrameInstruction()
{
#ifdef DMK_BUILD_STUDIO
	if (myImGuiBackend)
		myImGuiBackend->onRendererUpdate(currentImageIndex, mySwapChain, myDrawCallManager.getPrimaryCommandBuffer(currentImageIndex));

#endif

	myCoreObject->submitCommand(myDrawCallManager.getPrimaryCommandBuffer(currentImageIndex), mySwapChain);
	isPresenting = false;
}

void DMKRenderer::initializeImGuiClient(DMKImGuiBackendHandle** pAddressStore)
{
	myImGuiBackend = allocateImGuiClient();
	myImGuiBackend->setCoreObject(myCoreObject);
	myImGuiBackend->setRenderTarget(&myRenderTarget);

	myImGuiBackend->initialize();

	*pAddressStore = myImGuiBackend;
}

void DMKRenderer::submitUniformData()
{
	for (UI64 index = 0; index < myEntities.size(); index++)
		for (UI32 itr = 0; itr < myEntities[index]->uniformContainers.size(); itr++)
			myEntities[index]->uniformContainers[itr].pUniformBuffer->setData(myCoreObject, myEntities[index]->uniformContainers[itr].pParent->byteSize(), 0, myEntities[index]->uniformContainers[itr].pParent->data());
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
	/* Terminate draw call manager */
	myDrawCallManager.terminateAll(myCoreObject);

	/* Terminate Core Object */
	myCoreObject->terminate();
	StaticAllocator<RCoreObject>::rawDeallocate(myCoreObject, 0);
}

void DMKRenderer::terminateEnvironmentMap(REnvironmentEntity* pEnvironmentMap)
{
	if (pEnvironmentMap->renderEntity.pPipelineObject)
	{
		pEnvironmentMap->renderEntity.pPipelineObject->terminate(myCoreObject);
		StaticAllocator<RPipelineObject>::rawDeallocate(pEnvironmentMap->renderEntity.pPipelineObject, 0);
	}

	if (pEnvironmentMap->pTexture)
	{
		pEnvironmentMap->pTexture->terminate(myCoreObject);
		StaticAllocator<RTexture>::rawDeallocate(pEnvironmentMap->pTexture, 0);
	}

	for (auto pUniform : pEnvironmentMap->uniformBuffers)
	{
		pUniform.pUniformBuffer->terminate(myCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(pUniform.pUniformBuffer, 0);
	}

	if (pEnvironmentMap->pBRDFTable)
	{
		pEnvironmentMap->pBRDFTable->terminate(myCoreObject);
		StaticAllocator<RBRDFTable>::rawDeallocate(pEnvironmentMap->pBRDFTable, 0);
	}

	if (pEnvironmentMap->pIrradianceCube)
	{
		pEnvironmentMap->pIrradianceCube->terminate(myCoreObject);
		StaticAllocator<RIrradianceCube>::rawDeallocate(pEnvironmentMap->pIrradianceCube, 0);
	}

	if (pEnvironmentMap->pPreFilteredCube)
	{
		pEnvironmentMap->pPreFilteredCube->terminate(myCoreObject);
		StaticAllocator<RIrradianceCube>::rawDeallocate(pEnvironmentMap->pPreFilteredCube, 0);
	}

	if (pEnvironmentMap->renderEntity.pVertexBuffer)
	{
		pEnvironmentMap->renderEntity.pVertexBuffer->terminate(myCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(pEnvironmentMap->renderEntity.pVertexBuffer, 0);
	}

	if (pEnvironmentMap->renderEntity.pIndexBuffer)
	{
		pEnvironmentMap->renderEntity.pIndexBuffer->terminate(myCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(pEnvironmentMap->renderEntity.pIndexBuffer, 0);
	}
}

void DMKRenderer::terminateEntity(REntity* pEntity)
{
	for (auto uniform : pEntity->uniformContainers)
	{
		uniform.pUniformBuffer->terminate(myCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(uniform.pUniformBuffer, 0);
	}

	for (auto mesh : pEntity->meshObjects)
	{
		for (auto texture : mesh.pTextures)
		{
			texture->terminate(myCoreObject);
			StaticAllocator<RTexture>::rawDeallocate(texture, 0);
		}
	}
	pEntity->meshObjects.clear();

	if (pEntity->pPipelineObject)
	{
		pEntity->pPipelineObject->terminate(myCoreObject);

		for (auto block : pEntity->pPipelineObject->constantBlocks)
			StaticAllocator<BYTE>::rawDeallocate(block.data, block.byteSize);

		StaticAllocator<RPipelineObject>::rawDeallocate(pEntity->pPipelineObject, 0);
	}

	pEntity->pVertexBuffer->terminate(myCoreObject);
	StaticAllocator<RBuffer>::rawDeallocate(pEntity->pVertexBuffer, 0);

	pEntity->pIndexBuffer->terminate(myCoreObject);
	StaticAllocator<RBuffer>::rawDeallocate(pEntity->pIndexBuffer, 0);

	StaticAllocator<REntity>::rawDeallocate(pEntity);
}

void DMKRenderer::terminateEntities()
{
	/* Terminate Environment Map */
	terminateEnvironmentMap(&myCurrentEnvironment);

	/* Terminate Entities */
	for (auto entity : myEntities)
		terminateEntity(entity);

	myEntities.clear();

	/* Terminate Bounding Boxes */
	for (auto boundingBox : myBoundingBoxes)
		boundingBox.terminate(myCoreObject);

	myBoundingBoxes.clear();

	if (myImGuiBackend)
	{
		myImGuiBackend->terminate();
		StaticAllocator<RImGuiBackend>::rawDeallocate(myImGuiBackend, 0);
	}
}

RMeshObject DMKRenderer::createMeshObject(DMKStaticModelEntity* pStaticModel, DMKMeshObject* pMeshObject, RPipelineResource* pResource, RPipelineObject* pParentPipeline, ARRAY<RBuffer*> pUniformBuffers, UI32 meshIndex, UI32* pProgressMeter)
{
#define INC_PROGRESS if(pProgressMeter) (*pProgressMeter)++

	RMeshObject meshComponent;
	meshComponent.pParentObject = pMeshObject;

	/* Initialize Textures */
	for (auto texture : meshComponent.pParentObject->getMaterial().textureContainers)
		meshComponent.pTextures.pushBack(createTexture(texture.pTexture));
	INC_PROGRESS;

	/* Initialize Pipeline Resources */
	{
		/* Initialize Texture Resources */
		ARRAY<RTexture*> textures;
		textures.insert(meshComponent.pTextures);

		for (auto request : pStaticModel->getResourceRequests())
		{
			switch (request)
			{
			case DMKResourceRequest::DMK_RESOURCE_REQUEST_BRDF_TABLE:
				if (myCurrentEnvironment.pBRDFTable)
					textures.pushBack(myCurrentEnvironment.pBRDFTable->pTexture);
				else
					DMK_ERROR("An environment map is not submitted! Make sure to submit an environment map in order to provide resources.");
				break;

			case DMKResourceRequest::DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE:
				if (myCurrentEnvironment.pIrradianceCube)
					textures.pushBack(myCurrentEnvironment.pIrradianceCube->pTexture);
				else
					DMK_ERROR("An environment map is not submitted! Make sure to submit an environment map in order to provide resources.");
				break;

			case DMKResourceRequest::DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE:
				if (myCurrentEnvironment.pPreFilteredCube)
					textures.pushBack(myCurrentEnvironment.pPreFilteredCube->pTexture);
				else
					DMK_ERROR("An environment map is not submitted! Make sure to submit an environment map in order to provide resources.");
				break;

			default:
				DMK_ERROR("Invalid resource request!");
				break;
			}
		}
		INC_PROGRESS;

		pResource->update(myCoreObject, pUniformBuffers, textures);
		meshComponent.pResourceObject = pResource;

		/* Initialize Constant Blocks */
		pParentPipeline->submitConstantData(
			StaticAllocator<DMKMaterial::MaterialPushBlock>::allocateInit(meshComponent.pParentObject->getMaterial().generatePushBlock()), meshIndex);

		INC_PROGRESS;
	}

	meshComponent.vertexCount = pMeshObject->getVertexBuffer().size();
	meshComponent.indexCount = pMeshObject->getIndexBuffer().size();

	INC_PROGRESS;
	return meshComponent;
}
