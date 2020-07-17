// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RUtilities.h"

#include "VulkanRBL/Pipelines/VulkanGraphicsPipeline.h"
#include "VulkanRBL/Primitives/VulkanBuffer.h"

namespace Dynamik
{
	using namespace Backend;

	RPipelineObject* RUtilities::allocatePipeline(DMKRenderingAPI API)
	{
		switch (API)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
			return StaticAllocator<VulkanGraphicsPipeline>::rawAllocate();
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		}

		return nullptr;
	}

	RBuffer* RUtilities::allocateBuffer(DMKRenderingAPI API)
	{
		switch (API)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
			return StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		}

		return nullptr;
	}

	ARRAY<RColorBlendState> RUtilities::createBasicColorBlendStates()
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
	
	ARRAY<RSubPasses> RUtilities::createSubPasses(DMKRenderContextType contextType)
	{
		ARRAY<RSubPasses> subpasses;
		switch (contextType)
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

		return subpasses;
	}
}
