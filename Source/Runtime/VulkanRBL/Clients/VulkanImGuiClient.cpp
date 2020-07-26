// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanImGuiClient.h"

#include "../Primitives/VulkanTexture.h"
#include "../VulkanUtilities.h"

#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Tools/Shader/GLSL/Compiler.h"
#include "Renderer/RUtilities.h"

#include <imgui.h>

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImGuiClient::initialize()
		{
			/* Initialize Font Data */
			_initializeFontTexture();

			/* Initialize Pipeline */
			_initializePipeline();
		}

		void VulkanImGuiClient::update()
		{
		}

		void VulkanImGuiClient::drawFrame()
		{
		}

		void VulkanImGuiClient::terminate()
		{
			pPipelineObject->terminate(pCoreObject);
			StaticAllocator<VulkanGraphicsPipeline>::rawDeallocate(pPipelineObject);

			pFontTexture->terminate(pCoreObject);
			StaticAllocator<VulkanTexture>::rawDeallocate(pFontTexture);
		}

		void VulkanImGuiClient::_initializeFontTexture()
		{
			ImGuiIO& io = ImGui::GetIO();

			UCHR* fontData = nullptr;
			I32 width = 0, height = 0;
			io.Fonts->GetTexDataAsRGBA32(&fontData, &width, &height);
			VkDeviceSize uploadSize = Cast<I64>(width) * Cast<I64>(height) * Cast<I64>(4) * Cast<I64>(sizeof(CHR));

			pFontTexture = StaticAllocator<VulkanTexture>::rawAllocate();

			RImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.vDimentions.width = Cast<F32>(width);
			imageCreateInfo.vDimentions.height = Cast<F32>(height);
			imageCreateInfo.vDimentions.depth = 1.0f;
			imageCreateInfo.mipLevels = 1;
			imageCreateInfo.layers = 1;
			imageCreateInfo.sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.imageUsage = RImageUsage(RImageUsage::IMAGE_USAGE_RENDER | RImageUsage::IMAGE_USAGE_TRANSFER_DST);
			imageCreateInfo.imageFormat = DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;

			pFontTexture->pImage = StaticAllocator<VulkanImage>::rawAllocate();
			pFontTexture->pImage->initialize(pCoreObject, imageCreateInfo);

			pFontTexture->pImage->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

			VulkanUtilities::copyDataToImage(pCoreObject, pFontTexture->pImage, fontData, Cast<UI64>(uploadSize));

			pFontTexture->makeRenderable(pCoreObject);

			pFontTexture->pSampler = StaticAllocator<VulkanImageSampler>::rawAllocate();
			pFontTexture->pSampler->initialize(pCoreObject, RImageSamplerCreateInfo::createDefaultSampler());
		}

		void VulkanImGuiClient::_initializePipeline()
		{
			Tools::GLSLCompiler compiler;

			ARRAY<DMKShaderModule> shaders;
			shaders.pushBack(compiler.getSPIRV(DMKAssetRegistry::getAsset(TEXT("SHADER_IM_GUI_UI_VERT")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX));
			shaders.pushBack(compiler.getSPIRV(DMKAssetRegistry::getAsset(TEXT("SHADER_IM_GUI_UI_FRAG")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT));

			RPipelineSpecification pipelineSpec = {};
			pipelineSpec.dynamicStates = { RDynamicState::DYNAMIC_STATE_VIEWPORT, RDynamicState::DYNAMIC_STATE_SCISSOR };
			pipelineSpec.scissorInfos.resize(1);
			pipelineSpec.colorBlendInfo.blendStates = { createColorBlendState() };
			pipelineSpec.multiSamplingInfo.sampleCount = DMK_SAMPLE_COUNT_1_BIT;

			pPipelineObject = StaticAllocator<VulkanGraphicsPipeline>::rawAllocate();
			pPipelineObject->initialize(pCoreObject, pipelineSpec, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, nullptr, DMKViewport());
		
			pPipelineObject->initializeResources(pCoreObject, ARRAY<RBuffer*>(), { pFontTexture });
		}

		RColorBlendState VulkanImGuiClient::createColorBlendState()
		{
			RColorBlendState blendState = {};
			blendState.enable = true;
			blendState.colorWriteMask = RColorComponent(RColorComponent::COLOR_COMPONENT_R_BIT | RColorComponent::COLOR_COMPONENT_G_BIT | RColorComponent::COLOR_COMPONENT_B_BIT | RColorComponent::COLOR_COMPONENT_A_BIT);
			blendState.srcColorBlendFactor = RColorBlendFactor::COLOR_BLEND_FACTOR_SRC_ALPHA;
			blendState.dstColorBlendFactor = RColorBlendFactor::COLOR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			blendState.colorBlendOp = RColorBlendOp::COLOR_BLEND_OP_ADD;
			blendState.srcAlphaBlendFactor = RColorBlendFactor::COLOR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			blendState.dstAlphaBlendFactor = RColorBlendFactor::COLOR_BLEND_FACTOR_ZERO;
			blendState.alphaBlendOp = RColorBlendOp::COLOR_BLEND_OP_ADD;

			return blendState;
		}
	}
}
