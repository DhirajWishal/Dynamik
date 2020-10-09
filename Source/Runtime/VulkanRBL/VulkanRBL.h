// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_RENDERER_BACKEND_LAYER_H
#define _DYNAMIK_VULKAN_RENDERER_BACKEND_LAYER_H

#include "Renderer/RendererBackendLayer.h"

namespace Backend
{
	/*
	 Vulkan Renderer Backend Layer 
	*/
	class DMK_API VulkanRBL : public DMKRendererBackendLayer {
	public:
		VulkanRBL() {}
		~VulkanRBL() {}

		virtual void initializeCoreObject(DMKRendererDescription description) override final;
		virtual RCoreObject* getCoreObject()const override final;
		virtual void terminateCoreObject() override final;

		virtual RSwapChain* createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode) override final;
		virtual void terminateSwapChain(RSwapChain* pSwapChain) override final;

		virtual RRenderTarget* createRenderTarget(RSwapChain* pSwapChain, ARRAY<RSubpassAttachment> subPasses, ARRAY<RSubpassDependency> subPassDependencies) override final;
		virtual void terminateRenderTarget(RRenderTarget* pRenderTarget) override final;

		virtual RRenderPass* createRenderPass(RSwapChain* pSwapChain, ARRAY<RSubpassAttachment> subPasses, ARRAY<RSubpassDependency> subPassDependencies) override final;
		virtual void terminateRenderPass(RRenderPass* pRenderPass) override final;

		virtual RFrameBuffer* createFrameBuffer(RSwapChain* pSwapChain, RRenderPass* pRenderPass) override final;
		virtual void terminateFrameBuffer(RFrameBuffer* pFrameBuffer) override final;

		virtual RBuffer* createBuffer(RBufferType type, UI64 size, RResourceMemoryType memoryType = RResourceMemoryType(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT)) override final;
		virtual void terminateBuffer(RBuffer* pBuffer) override final;

		virtual RBuffer* createVertexBuffer(UI64 size) override final;
		virtual RBuffer* createIndexBuffer(UI64 size) override final;
		virtual RBuffer* createUniformBuffer(UI64 size) override final;

		virtual RTexture* createTexture(DMKTexture* pTexture) override final;
		virtual void terminateTexture(RTexture* pTexture) override final;

		virtual RPipelineObject* createPipeline(RPipelineSpecification specification, RPipelineUsage pipelineUsage, RRenderTarget* pRenderTarget, DMKViewport viewPort) override final;
		virtual void terminatePipeline(RPipelineObject* pPipelineObject) override final;

		virtual RBRDFTable* createBRDFTable(Vector2F dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RG_16_SF32) override final;
		virtual void terminateBRDFTable(RBRDFTable* pBRDFTable) override final;

		virtual RIrradianceCube* createIrradianceCube(REnvironmentEntity* pEnvironmentEntity, Vector2F dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_32_SF32) override final;
		virtual void terminateIrradianceCube(RIrradianceCube* pIrradianceCube) override final;

		virtual RPreFilteredCube* createPreFilteredCube(REnvironmentEntity* pEnvironmentEntity, Vector2F dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_16_SF32) override final;
		virtual void terminatePreFilteredCube(RPreFilteredCube* pPreFilteredCube) override final;

		virtual RImage* createStorageImage(DMKFormat format, Vector3F dimentions) override final;
		virtual void terminateImage(RImage* pImage) override final;
	};
}

#endif // !fine _VULKAN_RENDERER_BACKEND_LAYER_H
