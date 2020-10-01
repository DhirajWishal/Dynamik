// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ApplicationServer.h"
#include "Assets/Modules/Module00/Module00.h"

#include "Core/Error/ErrorManager.h"

void ApplicationServer::onInitializeSystems()
{
	/* Initialize the event pool. */
	initializeEventPool();

	/* Initialize the player controller. */
	initializePlayerController();

	/* Initialize the window. */
	initializeWindowHandle();

	/* Initialize the rendering engine. */
	initializeRenderingEngine();

	/* Create the rendering context. */
	getRenderer()->createContextCMD(getCurrentWindowHandle()->createViewport(512, 512, 0, 0), DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT);
}

void ApplicationServer::onInitializeServices()
{
	/* Initialize the basic services. */
	initializeBasicServices();

	/* Initialize the asset registry. */
	initializeAssetRegistry();

	/* Initialize the tools registry. */
	initializeToolsRegistry();
}

void ApplicationServer::onInitializeGame()
{
	loadGameModule(StaticAllocator<Module00>::allocate());
}

void ApplicationServer::onInitializeFinal()
{
	/* Initialize the renderer finals. */
	getRenderer()->initializeFinalsCMD();
}

void ApplicationServer::onBeginUpdate()
{
	/* Poll events from the current window handle. */
	getCurrentWindowHandle()->pollEvents();
}

void ApplicationServer::onUpdateGame()
{
	/* Update the game module. */
	getActiveGameModule()->onUpdate(1.0f);

	/* Update the entities of the current module. */
	getActiveGameModule()->updateEntities(1.0f);
}

void ApplicationServer::onUpdateSystems()
{
	/* Execute the player controls. */
	getPlayerController()->executeAll();

	/* Update the rendering engine. */
	getRenderer()->update();
}

void ApplicationServer::onEndUpdate()
{
	/* Clean the handled events from the window handle. */
	getCurrentWindowHandle()->clean();
}

void ApplicationServer::onTerminateGame()
{
	DMK_INFO("Game is terminated!");
}

void ApplicationServer::onTerminateSystems()
{
	/* Terminate the rendering engine. */
	terminateRenderingEngine();

	/* Terminate the window handle. */
	terminateWindowHandle();
}

void ApplicationServer::onTerminateServices()
{
	/* Terminate the basic services. */
	terminateBasicServices();
}

void ApplicationServer::onTerminateFinal()
{
}

DMK_SETUP_SERVER(ApplicationServer)

/////////////////////////////////////////////////////////////////////////////////////////////////////
///		Tests
/////////////////////////////////////////////////////////////////////////////////////////////////////

class DMKVertexBufferData {
public:
	DMKVertexBufferData(UI32 stride = 0, UI32 count = 0, void* data = nullptr)
		: stride(stride), count(count), data(data) {}
	~DMKVertexBufferData() {}

	UI32 stride = 0;
	UI32 count = 0;

	void* data = nullptr;
};

class DMKIndexBufferData {
public:
	DMKIndexBufferData(UI32 stride = 0, UI32 count = 0, void* data = nullptr)
		: stride(stride), count(count), data(data) {}
	~DMKIndexBufferData() {}

	UI32 stride = 0;
	UI32 count = 0;

	void* data = nullptr;
};

class DMKMeshHandle {
public:
	DMKMeshHandle() {}
	virtual ~DMKMeshHandle() {}

	virtual DMKVertexBufferData getPackedVertexData() { return DMKVertexBufferData(); }
	virtual DMKIndexBufferData getPackedIndexData() { return DMKIndexBufferData(); }
	virtual std::vector<DMKUniformBuffer> getUniformBuffers() { return std::vector<DMKUniformBuffer>(); }
	virtual std::vector<DMKTexture*> getTextures() { return std::vector<DMKTexture*>(); }
};

class DMKStaticMeshHandle : public DMKMeshHandle {};
class DMKAnimatedMeshHandle : public DMKMeshHandle {};

enum class DMKRenderPipelineType {
	DMK_RENDER_PIPELINE_TYPE_GRAPHICS,
	DMK_RENDER_PIPELINE_TYPE_COMPUTE,
	DMK_RENDER_PIPELINE_TYPE_RAY_TRACING,
};

struct DMKRenderSpecification { DMKRenderPipelineType pipelineType; };

/*
 This object defines what data are to be rendered in one rendering burst.
*/
class DMKRenderData {
public:
	DMKRenderData() {}
	~DMKRenderData() {}

	void addMeshHandle(DMKMeshHandle* pMeshHandle) { this->pMeshHandles.push_back(pMeshHandle); }

	std::vector<DMKMeshHandle*> pMeshHandles;
	DMKRenderSpecification renderSpecifications = {};	/* This resolves into one pipeline object. */
};

class StaticMesh : public DMKStaticMeshHandle {
public:
	StaticMesh() {}
	~StaticMesh() {}

	virtual DMKVertexBufferData getPackedVertexData() override final
	{
		return DMKVertexBufferData(sizeof(float), vertexData.size(), vertexData.data());
	}

	virtual DMKIndexBufferData getPackedIndexData() override final
	{
		return DMKIndexBufferData(sizeof(UI32), indexData.size(), indexData.data());
	}

	virtual std::vector<DMKUniformBuffer> getUniformBuffers()
	{
		return { uniform1, uniform2 };
	}

	std::vector<float> vertexData;
	std::vector<UI32> indexData;

	DMKUniformBuffer uniform1;
	DMKUniformBuffer uniform2;
};

void mainFunc()
{
	ObjectArray* pObjArray = nullptr;

	pObjArray->addObject<StaticMesh>(StaticMesh());
}
