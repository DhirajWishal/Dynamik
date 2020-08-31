// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_H
#define _DYNAMIK_RENDERER_H

#include "Core/Objects/System.h"
#include "RendererCommand.h"
#include "Managers/Thread/Thread.h"
#include "Managers/Thread/ThreadCommand.h"

#include "RendererBackendLayer.h"

#include "Components/RCoreObject.h"
#include "Components/Context/RFrameBuffer.h"
#include "Components/RCommandBufferManager.h"
#include "Components/Factories/BufferFactory.h"
#include "Components/REntity.h"
#include "Components/RCameraComponent.h"
#include "Components/REnvironmentEntity.h"
#include "Components/RDrawCallManager.h"
#include "Components/Attachments/RBoundingBox.h"
#include "Clients/RImGuiBackend.h"

class DMK_API DMKGameWorld;

/*
 Dynamik Renderer Compatibility structure
*/
struct DMK_API DMKRendererCompatibility {
	B1 isVulkanAvailable = false;
};

/*
 Renderer thread for the Dynamik Engine
 This is the base rendering API.
 This unit is executed on a single thread which manages all of its rendering commands sent via the thread
 commands.
*/
class DMK_API DMKRenderer : public DMKSystem, public DMKThread {
public:
	DMKRenderer() {}
	~DMKRenderer() {}

	/*
	 Initialize the thread.
	*/
	virtual void initializeThread() override final;

	/*
	 On Initialize call in the thread function.
	*/
	virtual void onInitialize() override final;

	/*
	 Process commands using its name.
	*/
	virtual void processCommand(STRING commandName) override final;

	/*
	 Execute the three steps of draw call.
	*/
	virtual void onLoop() override final;

	/*
	 Terminate the backend.
	*/
	virtual void onTermination() override final;

	/*
	 Terminate the thread.
	*/
	virtual void terminateThread() override final;

	/*
	 Initialize the internal components.
	*/
	virtual void initializeInternals() override final;

	/*
	 Terminate internal components.
	*/
	virtual void terminateInternals() override final;

public:		/* Command Interface */
	void issueRawCommand(RendererInstruction instruction);
	void initializeCMD(DMKRendererDescription description);
	void initializeFinalsCMD();
	void setSamplesCMD(DMKSampleCount samples);
	void setWindowHandleCMD(DMKWindowHandle* pWindowHandle);
	void createContextCMD(DMKViewport viewPort, DMKRenderContextType contextType);
	void update();

	void setImGuiContextCMD(ImGuiContext* pContext);

	/*
	 Initialize the environment entity command.

	 @param pEnvironmentEntity: The pointer to the environment entity.
	 @param pProgressMeter: The progress meter variable pointer. Default is nullptr. Maximum is 12.
	*/
	void initializeEnvironmentEntityCMD(DMKEnvironmentEntity* pEnvironmentEntity, UI32* pProgressMeter = nullptr);

	/*
	 Submit the static model entity to the renderer command.

	 @param pEntity: The static model entity pointer.
	 @param pProgressMeter: The progress meter variable pointer. Default is nullptr. Maximum is 5 + (4 * mesh object count).
	*/
	void submitStaticModelEntityCMD(DMKStaticModelEntity* pStaticModelEntity, UI32* pProgressMeter = nullptr);

	/*
	 Submit the animated model entity to the renderer command.

	 @param pEntity: The animated model entity pointer.
	 @param pProgressMeter: The progress meter variable pointer. Default is nullptr.
	*/
	void submitAnimatedModelEntityCMD(DMKAnimatedModelEntity* pAnimatedModelEntity, UI32* pProgressMeter = nullptr);

	/*
	 Remove a given static model from rendering.

	 @param pStaticModelEntity: The static model to be removed.
	*/
	void removeStaticModelEntityCMD(DMKStaticModelEntity* pStaticModelEntity);

	/*
	 Remove a given animated model from rendering.

	 @param pAnimatedModelEntity: The animated model to be removed.
	*/
	void removeAnimatedModelEntityCMD(DMKAnimatedModelEntity* pAnimatedModelEntity);

	/*
	 Remove the environment map from rendering.

	 @param pEnvironmentMapEntity: The environment map to be removed.
	*/
	void removeEnvironmentMapEntityCMD(DMKEnvironmentEntity* pEnvironmentMapEntity);

	void setFrameBufferResizeCMD(DMKExtent2D newExtent);
	void createImGuiClientCMD(DMKImGuiBackendHandle** returnAddressSpace);

	void submitPrimitiveCMD(DMKMeshObject* pMeshObject);
	void submitPrimitivesCMD(ARRAY<DMKMeshObject*> pMeshObjects);

private:    /* Core */
	void setSamples(const DMKSampleCount& samples);
	void setWindowHandle(const DMKWindowHandle* windowHandle);

private:    /* Context */
	void createContext(DMKRenderContextType type, DMKViewport viewport);

private:    /* Resource */
	RBuffer* createBuffer(const RBufferType& type, UI64 size, RResourceMemoryType memoryType = (RResourceMemoryType)
		(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	RBuffer* createVertexBuffer(UI64 size);
	RBuffer* createIndexBuffer(UI64 size);
	void copyBuffer(RBuffer* pSrcBuffer, RBuffer* pDstBuffer, UI64 size);
	void copyDataToBuffer(RBuffer* pDstBuffer, VPTR data, UI64 size, UI64 offset);

	RTexture* createTexture(const DMKTexture* pTexture);

	RImGuiBackend* allocateImGuiClient();

	/*
	 Max progress: 12
	*/
	void initializeEnvironmentEntity(DMKEnvironmentEntity* pEnvironmentEntity, UI32* pProgressMeter = nullptr);
	/*
	 Max progress: 5 + (4 * meshCount)
	*/
	void createStaticModelEntityResources(DMKStaticModelEntity* pEntity, UI32* pProgressMeter = nullptr);
	void createAnimatedModelEntityResources(DMKAnimatedModelEntity* pEntity, UI32* pProgressMeter = nullptr);

	void removeStaticModelEntityResources(DMKStaticModelEntity* pStaticModelEntity);
	void removeAnimatedModelEntityResources(DMKAnimatedModelEntity* pStaticModelEntity);
	void removeEnvironmentMapEntityResources(DMKEnvironmentEntity* pStaticModelEntity);

private:    /* Finals */
	void updateResources();
	void initializeCommandBuffers();
	void initializeFinals();

private:    /* Instructions */
	void resizeFrameBuffer(DMKExtent2D windowExtent);
	void beginFrameInstruction();
	void updateInstruction();
	void updateEnvironment();
	void updateEntities();
	void updateBoundingBoxes();
	void updateDebugObjects();
	void endFrameInstruction();
	void initializeImGuiClient(DMKImGuiBackendHandle** pAddressStore);

	void submitUniformData();

private:    /* Internal Methods */
	void terminateContext();
	void terminateComponents();
	void terminateEnvironmentMap(REnvironmentEntity* pEnvironmentMap);
	void terminateEntity(REntity* pEntity);
	void terminateEntities();

private:    /* Utility Methods */
	/* Max progress: 4 */
	RMeshObject createMeshObject(
		DMKStaticModelEntity* pStaticModel,
		DMKMeshObject* pMeshObject,
		RPipelineResource* pResource,
		RPipelineObject* pParentPipeline,
		ARRAY<RBuffer*> pUniformBuffers,
		UI32 meshIndex,
		UI32* pProgressMeter = nullptr);

	void createBackend();
	DMKRendererBackendLayer* getBackend() const;
	void terminateBackend();

private:    /* Internal */
	DMKRendererCompatibility myCompatibility;

	DMKRendererCommand* myCommand = nullptr;

	DMKRenderingAPI myAPI;
	RDrawCallManager myDrawCallManager;

	RSwapChain* mySwapChain = nullptr;
	RRenderTarget* myRenderTarget = nullptr;
	DMKRenderContextType myCurrentContextType = DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT;

	B1 isReadyToRun = false;

	RCameraComponent* myCameraComponent = nullptr;
	REnvironmentEntity myCurrentEnvironment;

	ARRAY<REntity*> myEntities;
	ARRAY<RBoundingBox> myBoundingBoxes;

	ARRAY<DMKStaticModelEntity*> pStaticEntities;
	ARRAY<DMKAnimatedModelEntity*> pAnimatedEntities;

	UI32 currentImageIndex = 0;

	DMKRendererBackendLayer* pCurrentBackendLayer = nullptr;

	B1 isPresenting = false;

private:    /* Factories */
	DMKBufferFactory myBufferFactory;

private:
	RImGuiBackend* myImGuiBackend = nullptr;
};

#endif // !_DYNAMIK_RENDERER_THREAD_H
