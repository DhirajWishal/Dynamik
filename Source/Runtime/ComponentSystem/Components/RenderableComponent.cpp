// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RenderableComponent.h"

namespace Dynamik
{
	void DMKRenderableComponent::addShaderModule(const DMKShaderModule& sModule)
	{
		shaderModules.pushBack(sModule);
	}

	void DMKRenderableComponent::addTextureModule(DMKTexture* pTexture)
	{
		textureModules.pushBack(pTexture);
	}

	void DMKRenderableComponent::setBaseRenderingPipeline(const DMKBaseRenderingPipeline& pipeline)
	{
		basePipeline = pipeline;
	}

	void DMKRenderableComponent::addRenderableComponent(DMKRenderableComponent* component)
	{
		renderComponents.pushBack(component);
	}

	void Dynamik::DMKRenderableComponent::setCameraModule(DMKCameraModule* cModule)
	{
		cameraModule = cModule;
	}
	
	void DMKRenderableComponent::setBindingIndex(const UI32& index)
	{
		uniformDescription.destinationBinding = index;
	}
}
