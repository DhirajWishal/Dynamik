// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RBoundingBox.h"

#include "../../RUtilities.h"

#include "VulkanRBL/Pipelines/VulkanGraphicsPipeline.h"
#include "VulkanRBL/Primitives/VulkanBuffer.h"

#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Utilities/ShaderFactory.h"

void RBoundingBox::initialize(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, RBuffer* pCameraUniform)
{
	/* Resolve Shaders */
	shaders.push_back(DMKShaderFactory::createModule(
		DMKAssetRegistry::getAsset(TEXT("SHADER_BOUNDING_BOX_VERT_SPV")),
		DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX,
		DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	shaders.push_back(DMKShaderFactory::createModule(
		DMKAssetRegistry::getAsset(TEXT("SHADER_BOUNDING_BOX_FRAG_SPV")),
		DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT,
		DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

	/* Initialize Pipeline */
	RPipelineSpecification pipelineSpecification = {};
	pipelineSpecification.resourceCount = 1;
	pipelineSpecification.shaders = shaders;
	pipelineSpecification.scissorInfos.resize(1);
	pipelineSpecification.multiSamplingInfo.sampleCount = pCoreObject->sampleCount;
	pipelineSpecification.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
	pipelineSpecification.primitiveAssemblyInfo.primitiveTopology = RPrimitiveTopology::PRIMITIVE_TOPOLOGY_LINE_LIST;
	pPipeline = RUtilities::allocatePipeline(renderingAPI);
	pPipeline->initialize(pCoreObject, pipelineSpecification, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, pRenderTarget, pSwapChain->viewPort);

	/* Initialize Uniforms */
	pUniformBuffer = RUtilities::allocateBuffer(renderingAPI);
	//pUniformBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_UNIFORM, pBoundingBox->uniformBufferObject.byteSize());
	//pUniformBuffer->setData(pCoreObject, pBoundingBox->uniformBufferObject.byteSize(), 0, pBoundingBox->uniformBufferObject.data());

	/* Update Resources */
	std::vector<RBuffer*> pBuffers;
	pBuffers.push_back(pUniformBuffer);

	if (pCameraUniform)
		pBuffers.push_back(pCameraUniform);

	pPipelineResource = pPipeline->allocateResources(pCoreObject)[0];
	pPipelineResource->update(pCoreObject, pBuffers, std::vector<RTexture*>());
}

void RBoundingBox::terminate(RCoreObject* pCoreObject)
{
	pPipeline->terminate(pCoreObject);
	StaticAllocator<RPipelineObject>::rawDeallocate(pPipeline, 0);

	pUniformBuffer->terminate(pCoreObject);
	StaticAllocator<RBuffer>::rawDeallocate(pUniformBuffer, 0);
}
