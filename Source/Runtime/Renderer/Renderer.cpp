// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Renderer.h"

#include "RUtilities.h"

#include "Core/Math/MathFunctions.h"
#include "Services/RuntimeSystems/AssetRegistry.h"

/* Vulkan headers */
#include "VulkanRBL/VulkanRBL.h"
#include "VulkanRBL/Clients/VulkanImGuiBackend.h"
#include <GLFW/glfw3.h>

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
			getBackend()->getCoreObject()->idleCall();
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

	else if (commandName == typeid(RendererInitialize).name())
		getBackend()->initializeCoreObject(pCommandService->getCommand<RendererInitialize>().description);

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
	myDrawCallManager.update(myRenderTarget, mySwapChain, currentImageIndex);

	/* Update the Im Gui client */
	if (myImGuiBackend)
		myImGuiBackend->onRendererUpdate(currentImageIndex, mySwapChain, myDrawCallManager.getPrimaryCommandBuffer(currentImageIndex));

	endFrameInstruction();
}

void DMKRenderer::onTermination()
{
	getBackend()->getCoreObject()->idleCall();

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
	createBackend();

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

void DMKRenderer::initializeCMD(DMKRendererDescription description)
{
	RendererInitialize _command;
	_command.description = description;

	pCommandService->issueCommand<RendererInitialize>(_command);
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

void DMKRenderer::update()
{
	issueRawCommand(RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE);
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
	getBackend()->setSampleCount(samples);
}

void DMKRenderer::setWindowHandle(const DMKWindowHandle* windowHandle)
{
	getBackend()->setWindowHandle(Cast<DMKWindowHandle*>(windowHandle));
}

void DMKRenderer::createContext(DMKRenderContextType type, DMKViewport viewport)
{
	myCurrentContextType = type;

	/* Initialize Swap chain */
	mySwapChain = getBackend()->createSwapChain(viewport, RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_FIFO);

	/* Initialize Render pass */
	myRenderTarget = getBackend()->createRenderTarget(mySwapChain, RUtilities::createSubPasses(myCurrentContextType, getBackend()->getCoreObject(), mySwapChain), { RSubpassDependency() });
}

RBuffer* DMKRenderer::createBuffer(const RBufferType& type, UI64 size, RResourceMemoryType memoryType)
{
	return getBackend()->createBuffer(type, size, memoryType);
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
	pDstBuffer->copy(getBackend()->getCoreObject(), pSrcBuffer, size, 0, 0);
}

void DMKRenderer::copyDataToBuffer(RBuffer* pDstBuffer, VPTR data, UI64 size, UI64 offset)
{
	auto staggingBuffer = createBuffer(RBufferType::BUFFER_TYPE_STAGGING, size);
	staggingBuffer->setData(getBackend()->getCoreObject(), size, offset, data);

	copyBuffer(staggingBuffer, pDstBuffer, size);

	staggingBuffer->terminate(getBackend()->getCoreObject());
	StaticAllocator<RBuffer>::rawDeallocate(staggingBuffer, 0);
}

RTexture* DMKRenderer::createTexture(const DMKTexture* pTexture)
{
	return getBackend()->createTexture(Cast<DMKTexture*>(pTexture));
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
	myCurrentEnvironment.renderEntity.pVertexBuffer->setData(getBackend()->getCoreObject(), pEnvironmentEntity->skyBoxMesh.getVertexBuffer().byteSize(), 0, pEnvironmentEntity->skyBoxMesh.getVertexBuffer().data());
	renderMesh.vertexCount = pEnvironmentEntity->skyBoxMesh.vertexBuffer.size();
	INC_PROGRESS;

	/* Initialize Index Buffer */
	myCurrentEnvironment.renderEntity.pIndexBuffer = createIndexBuffer(pEnvironmentEntity->skyBoxMesh.getIndexBuffer().byteSize());
	myCurrentEnvironment.renderEntity.pIndexBuffer->setData(getBackend()->getCoreObject(), pEnvironmentEntity->skyBoxMesh.getIndexBuffer().byteSize(), 0, pEnvironmentEntity->skyBoxMesh.getIndexBuffer().data());
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
			_container.pUniformBuffer->setData(getBackend()->getCoreObject(), _container.pParent->byteSize(), 0, _container.pParent->data());

			uniformBuffers.pushBack(_container.pUniformBuffer);
			myCurrentEnvironment.uniformBuffers.pushBack(_container);

			INC_PROGRESS;
		}
	}

	/* Initialize Pipeline */
	RPipelineSpecification pipelineCreateInfo = {};
	pipelineCreateInfo.resourceCount = 1;
	pipelineCreateInfo.shaders = pEnvironmentEntity->shaders;
	pipelineCreateInfo.scissorInfos.resize(1);
	pipelineCreateInfo.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
	pipelineCreateInfo.multiSamplingInfo.sampleCount = getBackend()->getCoreObject()->sampleCount;
	pipelineCreateInfo.rasterizerInfo.frontFace = RFrontFace::FRONT_FACE_CLOCKWISE;

	myCurrentEnvironment.renderEntity.pPipelineObject = getBackend()->createPipeline(pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, myRenderTarget, mySwapChain->viewPort);
	INC_PROGRESS;

	/* Initialize Resources */
	{
		Vector2F dim = { 512.0f, 512.0f };

		/* Initialize the BRDF table */
		myCurrentEnvironment.pBRDFTable = getBackend()->createBRDFTable(dim);
		INC_PROGRESS;

		/* Initialize the irradiance cube */
		myCurrentEnvironment.pIrradianceCube = getBackend()->createIrradianceCube(&myCurrentEnvironment, dim);
		INC_PROGRESS;

		/* Initialize the pre filtered cube */
		myCurrentEnvironment.pPreFilteredCube = getBackend()->createPreFilteredCube(&myCurrentEnvironment, dim);
	}
	INC_PROGRESS;

	/* Initialize Texture Resources */
	ARRAY<RTexture*> textures = { myCurrentEnvironment.pTexture };

	/* Initialize Pipeline Resources */
	renderMesh.pResourceObject = myCurrentEnvironment.renderEntity.pPipelineObject->allocateResources(getBackend()->getCoreObject())[0];
	renderMesh.pResourceObject->update(getBackend()->getCoreObject(), uniformBuffers, textures);
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
	pipelineCreateInfo.multiSamplingInfo.sampleCount = getBackend()->getCoreObject()->sampleCount;
	pRenderEntity->pPipelineObject = getBackend()->createPipeline(pipelineCreateInfo, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, myRenderTarget, mySwapChain->viewPort);
	INC_PROGRESS;

	auto resources = pRenderEntity->pPipelineObject->allocateResources(getBackend()->getCoreObject());

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
				_container.pUniformBuffer->setData(getBackend()->getCoreObject(), _container.pParent->byteSize(), 0, _container.pParent->data());

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
			POINTER<BYTE> vertexPtr = pRenderEntity->pVertexBuffer->getData(getBackend()->getCoreObject(), vertexBufferSize, 0);

			for (auto rMeshObject : pRenderEntity->meshObjects)
			{
				DMKMemoryFunctions::copyData(vertexPtr.get(), rMeshObject.pParentObject->getVertexBuffer().data(), rMeshObject.pParentObject->getVertexBuffer().byteSize());
				vertexPtr += rMeshObject.pParentObject->getVertexBuffer().byteSize();
			}

			pRenderEntity->pVertexBuffer->flushMemory(getBackend()->getCoreObject());
		}
		INC_PROGRESS;

		/* initialize index buffer */
		{
			pRenderEntity->pIndexBuffer = createIndexBuffer(indexBufferSize);
			POINTER<BYTE> indexPtr = pRenderEntity->pIndexBuffer->getData(getBackend()->getCoreObject(), indexBufferSize, 0);

			for (auto rMeshObject : pRenderEntity->meshObjects)
			{
				DMKMemoryFunctions::copyData(indexPtr.get(), rMeshObject.pParentObject->getIndexBuffer().data(), rMeshObject.pParentObject->getIndexBuffer().byteSize());
				indexPtr += rMeshObject.pParentObject->getIndexBuffer().byteSize();
			}

			pRenderEntity->pIndexBuffer->flushMemory(getBackend()->getCoreObject());
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
	getBackend()->getCoreObject()->idleCall();

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
	myDrawCallManager.resetPrimaryCommandBuffers(getBackend()->getCoreObject());
	myDrawCallManager.resetSecondaryCommandBuffers(getBackend()->getCoreObject());

	myDrawCallManager.reCreateBuffers(getBackend()->getCoreObject(), myRenderTarget, mySwapChain, myAPI);
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
	myDrawCallManager.initializeCommandBuffers(getBackend()->getCoreObject(), myRenderTarget, mySwapChain, myAPI);
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
	getBackend()->getCoreObject()->idleCall();
	myDrawCallManager.resetPrimaryCommandBuffers(getBackend()->getCoreObject());

	/* Terminate The Current Context */
	{
		/* Terminate Frame Buffer */
		myRenderTarget->pFrameBuffer->terminate(getBackend()->getCoreObject());

		/* Terminate Render Pass */
		myRenderTarget->pRenderPass->terminate(getBackend()->getCoreObject());

		/* Terminate Swap Chain */
		mySwapChain->terminate(getBackend()->getCoreObject());
	}

	/* Create New Context */
	{
		/* Initialize View port */
		DMKViewport newViewPort;
		newViewPort.windowHandle = getBackend()->getWindowHandle();
		newViewPort.width = (I32)windowExtent.width;
		newViewPort.height = (I32)windowExtent.height;

		/* Initialize Swap Chain */
		mySwapChain->initialize(getBackend()->getCoreObject(), newViewPort, RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_FIFO);

		/* Initialize Render Pass */
		myRenderTarget->pRenderPass->initialize(getBackend()->getCoreObject(), RUtilities::createSubPasses(myCurrentContextType, getBackend()->getCoreObject(), mySwapChain), { RSubpassDependency() }, mySwapChain);

		/* Initialize Frame Buffer */
		myRenderTarget->pFrameBuffer->initialize(getBackend()->getCoreObject(), myRenderTarget->pRenderPass, mySwapChain->extent, mySwapChain->bufferCount, RUtilities::getFrameBufferAttachments(myAPI, myRenderTarget->pRenderPass->subPasses, getBackend()->getCoreObject(), mySwapChain, mySwapChain->extent));
	}

	/* Initialize Pipelines */
	{
		/* Initialize Environment Map Pipeline */
		if (myCurrentEnvironment.renderEntity.pPipelineObject)
			myCurrentEnvironment.renderEntity.pPipelineObject->reCreate(getBackend()->getCoreObject(), myRenderTarget, mySwapChain->viewPort);

		/* Initialize Entity Pipelines */
		for (auto entity : myEntities)
			entity->pPipelineObject->reCreate(getBackend()->getCoreObject(), myRenderTarget, mySwapChain->viewPort);

		/* Initialize Bounding Boxes */
		for (auto box : myBoundingBoxes)
			box.pPipeline->reCreate(getBackend()->getCoreObject(), myRenderTarget, mySwapChain->viewPort);
	}

	/* Recreate Im Gui Backend Pipeline. */
	if (myImGuiBackend)
		myImGuiBackend->reCreatePipeline(myRenderTarget, mySwapChain->viewPort);

	/* Initialize Buffers */
	myDrawCallManager.reCreateBuffers(getBackend()->getCoreObject(), myRenderTarget, mySwapChain, myAPI);

	isReadyToRun = true;
}

void DMKRenderer::beginFrameInstruction()
{
	isPresenting = true;

	currentImageIndex = getBackend()->getCoreObject()->prepareFrame(mySwapChain);

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
		pUniform.pUniformBuffer->setData(getBackend()->getCoreObject(), pUniform.pParent->byteSize(), 0, pUniform.pParent->data());
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
	//	boundingBox.pUniformBuffer->setData(getBackend()->getCoreObject(), boundingBox.pBoundingBox->getUniform().byteSize(), 0, boundingBox.pBoundingBox->getUniform().data());
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

	getBackend()->getCoreObject()->submitCommand(myDrawCallManager.getPrimaryCommandBuffer(currentImageIndex), mySwapChain);
	isPresenting = false;
}

void DMKRenderer::initializeImGuiClient(DMKImGuiBackendHandle** pAddressStore)
{
	myImGuiBackend = allocateImGuiClient();
	myImGuiBackend->setCoreObject(getBackend()->getCoreObject());
	myImGuiBackend->setRenderTarget(myRenderTarget);

	myImGuiBackend->initialize();

	*pAddressStore = myImGuiBackend;
}

void DMKRenderer::submitUniformData()
{
	for (UI64 index = 0; index < myEntities.size(); index++)
		for (UI32 itr = 0; itr < myEntities[index]->uniformContainers.size(); itr++)
			myEntities[index]->uniformContainers[itr].pUniformBuffer->setData(getBackend()->getCoreObject(), myEntities[index]->uniformContainers[itr].pParent->byteSize(), 0, myEntities[index]->uniformContainers[itr].pParent->data());
}

void DMKRenderer::terminateContext()
{
	/* Terminate Render Target */
	getBackend()->terminateRenderTarget(myRenderTarget);

	/* Terminate Swap Chain */
	getBackend()->terminateSwapChain(mySwapChain);
}

void DMKRenderer::terminateComponents()
{
	/* Terminate draw call manager */
	myDrawCallManager.terminateAll(getBackend()->getCoreObject());

	/* Terminate Core Object */
	getBackend()->terminateCoreObject();

	/* Terminate Backend */
	terminateBackend();
}

void DMKRenderer::terminateEnvironmentMap(REnvironmentEntity* pEnvironmentMap)
{
	if (pEnvironmentMap->renderEntity.pPipelineObject)
		getBackend()->terminatePipeline(pEnvironmentMap->renderEntity.pPipelineObject);

	if (pEnvironmentMap->pTexture)
		getBackend()->terminateTexture(pEnvironmentMap->pTexture);

	for (auto pUniform : pEnvironmentMap->uniformBuffers)
		getBackend()->terminateBuffer(pUniform.pUniformBuffer);

	if (pEnvironmentMap->pBRDFTable)
		getBackend()->terminateBRDFTable(pEnvironmentMap->pBRDFTable);

	if (pEnvironmentMap->pIrradianceCube)
		getBackend()->terminateIrradianceCube(pEnvironmentMap->pIrradianceCube);

	if (pEnvironmentMap->pPreFilteredCube)
		getBackend()->terminatePreFilteredCube(pEnvironmentMap->pPreFilteredCube);

	if (pEnvironmentMap->renderEntity.pVertexBuffer)
		getBackend()->terminateBuffer(pEnvironmentMap->renderEntity.pVertexBuffer);

	if (pEnvironmentMap->renderEntity.pIndexBuffer)
		getBackend()->terminateBuffer(pEnvironmentMap->renderEntity.pIndexBuffer);
}

void DMKRenderer::terminateEntity(REntity* pEntity)
{
	for (auto uniform : pEntity->uniformContainers)
		getBackend()->terminateBuffer(uniform.pUniformBuffer);

	for (auto mesh : pEntity->meshObjects)
		for (auto texture : mesh.pTextures)
			getBackend()->terminateTexture(texture);

	pEntity->meshObjects.clear();

	if (pEntity->pPipelineObject)
		getBackend()->terminatePipeline(pEntity->pPipelineObject);

	getBackend()->terminateBuffer(pEntity->pVertexBuffer);
	getBackend()->terminateBuffer(pEntity->pIndexBuffer);

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
		boundingBox.terminate(getBackend()->getCoreObject());

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

		pResource->update(getBackend()->getCoreObject(), pUniformBuffers, textures);
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

void DMKRenderer::createBackend()
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		pCurrentBackendLayer = StaticAllocator<VulkanRBL>::allocate();
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		DMK_ERROR("Invalid rendering API!");
		break;
	}
}

DMKRendererBackendLayer* DMKRenderer::getBackend() const
{
	return pCurrentBackendLayer;
}

void DMKRenderer::terminateBackend()
{
	switch (myAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		StaticAllocator<VulkanRBL>::deallocate(pCurrentBackendLayer);
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		DMK_ERROR("Invalid rendering API!");
		break;
	}
}
