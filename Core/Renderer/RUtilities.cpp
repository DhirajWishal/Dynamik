// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RUtilities.h"

#include "Components/Context/RFrameBufferAttachment.h"

#include "VulkanRBL/Pipelines/VulkanGraphicsPipeline.h"
#include "VulkanRBL/Primitives/VulkanBuffer.h"

#include "VulkanRBL/Context/Attachments/VulkanColorAttachment.h"
#include "VulkanRBL/Context/Attachments/VulkanDepthAttachment.h"

using namespace Backend;

RPipelineObject* RUtilities::allocatePipeline(DMKRenderingAPI API)
{
	switch (API)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanGraphicsPipeline>::rawAllocate();
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	}

	return nullptr;
}

RBuffer* RUtilities::allocateBuffer(DMKRenderingAPI API)
{
	switch (API)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	}

	return nullptr;
}

std::vector<RColorBlendState> RUtilities::createBasicColorBlendStates()
{
	std::vector<RColorBlendState> blendStates;
	RColorBlendState state;
	for (UI32 index = 0; index < 1; index++)
	{
		state.colorWriteMask = RColorComponent(RColorComponent::COLOR_COMPONENT_R_BIT | RColorComponent::COLOR_COMPONENT_G_BIT | RColorComponent::COLOR_COMPONENT_B_BIT | RColorComponent::COLOR_COMPONENT_A_BIT);
		state.enable = false;

		blendStates.push_back(state);
	}

	return blendStates;
}

std::vector<RSubpassAttachment> RUtilities::createSubPasses(DMKRenderContextType contextType, RCoreObject* pCoreObject, RSwapChain* pSwapChain)
{
	std::vector<RSubpassAttachment> subpasses;
	switch (contextType)
	{
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT:
		subpasses.push_back(RSubpassAttachment::createColor(pSwapChain->format, pCoreObject->sampleCount));
		subpasses.push_back(RSubpassAttachment::createDepth(pCoreObject));
		subpasses.push_back(RSubpassAttachment::createSwapChain(pSwapChain));
		break;
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT_VR:
		subpasses.push_back(RSubpassAttachment::createColor(pSwapChain->format, pCoreObject->sampleCount));
		subpasses.push_back(RSubpassAttachment::createDepth(pCoreObject));
		subpasses.push_back(RSubpassAttachment::createSwapChain(pSwapChain));
		break;
	case DMKRenderContextType::DMK_RENDER_CONTEXT_2D:
		subpasses.push_back(RSubpassAttachment::createColor(pSwapChain->format, pCoreObject->sampleCount));
		subpasses.push_back(RSubpassAttachment::createSwapChain(pSwapChain));
		break;
	case DMKRenderContextType::DMK_RENDER_CONTEXT_3D:
		subpasses.push_back(RSubpassAttachment::createColor(pSwapChain->format, pCoreObject->sampleCount));
		subpasses.push_back(RSubpassAttachment::createDepth(pCoreObject));
		subpasses.push_back(RSubpassAttachment::createSwapChain(pSwapChain));
		break;
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG:
		subpasses.push_back(RSubpassAttachment::createColor(pSwapChain->format, pCoreObject->sampleCount));
		subpasses.push_back(RSubpassAttachment::createDepth(pCoreObject));
		subpasses.push_back(RSubpassAttachment::createSwapChain(pSwapChain));
		break;
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG_VR:
		subpasses.push_back(RSubpassAttachment::createColor(pSwapChain->format, pCoreObject->sampleCount));
		subpasses.push_back(RSubpassAttachment::createDepth(pCoreObject));
		subpasses.push_back(RSubpassAttachment::createSwapChain(pSwapChain));
		break;
	default:
		DMK_ERROR_BOX("Invalid context type!");
		break;
	}

	return subpasses;
}

std::vector<RSubPasses> RUtilities::getSubpassNames(DMKRenderContextType contextType)
{
	switch (contextType)
	{
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT:
		return { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT_VR:
		return { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
	case DMKRenderContextType::DMK_RENDER_CONTEXT_2D:
		return { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_SWAPCHAIN };
	case DMKRenderContextType::DMK_RENDER_CONTEXT_3D:
		return { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG:
		return { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
	case DMKRenderContextType::DMK_RENDER_CONTEXT_DEBUG_VR:
		return { RSubPasses::SUBPASSES_COLOR, RSubPasses::SUBPASSES_DEPTH, RSubPasses::SUBPASSES_SWAPCHAIN };
	default:
		DMK_ERROR("Invalid context type!");
		break;
	}

	return std::vector<RSubPasses>();
}

DMK_FORCEINLINE RFrameBufferAttachment* allocateColorAttachment(DMKRenderingAPI API)
{
	switch (API)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanColorAttachment>::rawAllocate();
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		DMK_ERROR("Invalid rendering API!");
		break;
	}

	return nullptr;
}

DMK_FORCEINLINE RFrameBufferAttachment* allocateDepthAttachment(DMKRenderingAPI API)
{
	switch (API)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_NONE:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		return StaticAllocator<VulkanDepthAttachment>::rawAllocate();
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		DMK_ERROR("Invalid rendering API!");
		break;
	}

	return nullptr;
}

DMK_FORCEINLINE RFrameBufferAttachment* allocateSwapChainAttachment(DMKRenderingAPI API)
{
	return StaticAllocator<RFrameBufferAttachment>::rawAllocate();
}

std::vector<std::vector<RFrameBufferAttachment*>> RUtilities::getFrameBufferAttachments(DMKRenderingAPI API, std::vector<RSubpassAttachment> subPassAttachments, RCoreObject* pCoreObject, RSwapChain* pSwapChain, DMKExtent2D imageExtent)
{
	UI32 bufferCount = pSwapChain->bufferCount;
	std::vector<std::vector<RFrameBufferAttachment*>> attachments;

	if (pSwapChain->bufferCount != bufferCount)
		DMK_FATAL("Invalid buffer count or swap chain image count!");

	for (UI32 index = 0; index < bufferCount; index++)
	{
		std::vector<RFrameBufferAttachment*> attachment;
		for (auto subPass : subPassAttachments)
		{
			RFrameBufferAttachmentInfo initInfo;
			initInfo.format = subPass.format;
			initInfo.msaaSamples = subPass.samples;
			initInfo.imageWidth = Cast<UI32>(imageExtent.width);
			initInfo.imageHeight = Cast<UI32>(imageExtent.height);

			RFrameBufferAttachment* pAttachment = nullptr;
			switch (subPass.subpass)
			{
			case RSubPasses::SUBPASSES_UNDEFINED:
				DMK_ERROR("Submitted sub pass in undefined!");
				break;
			case RSubPasses::SUBPASSES_SWAPCHAIN:
				pAttachment = allocateSwapChainAttachment(API);
				pAttachment->setImage(pSwapChain->images[index]);
				break;
			case RSubPasses::SUBPASSES_DEPTH:
				pAttachment = allocateDepthAttachment(API);
				pAttachment->initialize(pCoreObject, initInfo);
				break;
			case RSubPasses::SUBPASSES_COLOR:
				pAttachment = allocateColorAttachment(API);
				pAttachment->initialize(pCoreObject, initInfo);
				break;
			case RSubPasses::SUBPASSES_OVERLAY:
				break;
			default:
				DMK_ERROR("Unsupported sub pass type!");
				break;
			}

			attachment.push_back(pAttachment);
		}

		attachments.push_back(attachment);
	}

	return attachments;
}

RTexture* RUtilities::createBRDFTable(RCoreObject* pCoreObject, float dimentions)
{
	return nullptr;
}