// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_BACKEND_LAYER_H
#define _DYNAMIK_RENDERER_BACKEND_LAYER_H

#include "Components/RCoreObject.h"
#include "Components/ContextTypeDefs.h"
#include "Components/Lighting/RBRDFTable.h"
#include "Components/Lighting/RIrradianceCube.h"
#include "Components/Lighting/RPreFilteredCube.h"

#include "RUtilities.h"

/*
 Dynamik Renderer Backend Layer
 This object is the base class for the renderer backend layer.
*/
class DMK_API DMKRendererBackendLayer {
public:
	DMKRendererBackendLayer() {}
	virtual ~DMKRendererBackendLayer() {}

	void setSampleCount(DMKSampleCount sampleCount) { this->sampleCount = sampleCount; }
	DMKSampleCount getSampleCount() const { return this->sampleCount; }

	void setWindowHandle(DMKWindowHandle* pWindowHandle) { this->pWindowHandle = pWindowHandle; }
	DMKWindowHandle* getWindowHandle() const { return this->pWindowHandle; }

	virtual void initializeCoreObject(DMKRendererDescription description) {}
	virtual RCoreObject* getCoreObject() const { return pCoreObject; }
	virtual void terminateCoreObject() {}

	virtual RSwapChain* createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode) { return nullptr; }
	virtual void terminateSwapChain(RSwapChain* pSwapChain) {}

	virtual RRenderTarget* createRenderTarget(RSwapChain* pSwapChain, ARRAY<RSubpassAttachment> subPasses, ARRAY<RSubpassDependency> subPassDependencies) { return nullptr; }
	virtual void terminateRenderTarget(RRenderTarget* pRenderTarget) {}

	virtual RRenderPass* createRenderPass(RSwapChain* pSwapChain, ARRAY<RSubpassAttachment> subPasses, ARRAY<RSubpassDependency> subPassDependencies) { return nullptr; }
	virtual void terminateRenderPass(RRenderPass* pRenderPass) {}

	virtual RFrameBuffer* createFrameBuffer(RSwapChain* pSwapChain, RRenderPass* pRenderPass) { return nullptr; }
	virtual void terminateFrameBuffer(RFrameBuffer* pFrameBuffer) {}

	virtual RBuffer* createBuffer(RBufferType type, UI64 size, RResourceMemoryType memoryType = RResourceMemoryType(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT)) { return nullptr; }
	virtual void terminateBuffer(RBuffer* pBuffer) {}

	virtual RBuffer* createVertexBuffer(UI64 size) { return nullptr; }
	virtual RBuffer* createIndexBuffer(UI64 size) { return nullptr; }
	virtual RBuffer* createUniformBuffer(UI64 size) { return nullptr; }

	virtual RTexture* createTexture(DMKTexture* pTexture) { return nullptr; }
	virtual void terminateTexture(RTexture* pTexture) {}

	virtual RPipelineObject* createPipeline(RPipelineSpecification specification, RPipelineUsage pipelineUsage, RRenderTarget* pRenderTarget, DMKViewport viewPort) { return nullptr; }
	virtual void terminatePipeline(RPipelineObject* pPipelineObject) {}

	virtual RBRDFTable* createBRDFTable(Vector2F dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RG_16_SF32) { return nullptr; }
	virtual void terminateBRDFTable(RBRDFTable* pBRDFTable) {}

	virtual RIrradianceCube* createIrradianceCube(REnvironmentEntity* pEnvironmentEntity, Vector2F dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_32_SF32) { return nullptr; }
	virtual void terminateIrradianceCube(RIrradianceCube* pIrradianceCube) {}

	virtual RPreFilteredCube* createPreFilteredCube(REnvironmentEntity* pEnvironmentEntity, Vector2F dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_16_SF32) { return nullptr; }
	virtual void terminatePreFilteredCube(RPreFilteredCube* pPreFilteredCube) {}

	virtual RImage* createStorageImage(DMKFormat format, Vector3F dimentions) { return nullptr; }
	virtual void terminateImage(RImage* pImage) {}
protected:
	RCoreObject* pCoreObject = nullptr;
	DMKWindowHandle* pWindowHandle = nullptr;

	DMKSampleCount sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_64_BIT;
};

#endif // !_DYNAMIK_RENDERER_BACKEND_LAYER_H
