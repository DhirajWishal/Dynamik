// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RenderableComponent.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKRenderableComponent::addShaderModule(const DMKShaderModule& sModule)
	{
		shaderModules.pushBack(sModule);
	}

	void DMKRenderableComponent::clearShaderModules()
	{
		shaderModules.clear();
	}

	void DMKRenderableComponent::addTextureModule(DMKTexture* pTexture)
	{
		pTextures.pushBack(pTexture);
	}

	void DMKRenderableComponent::setBaseRenderingPipeline(const DMKBaseRenderingPipeline& pipeline)
	{
		basePipeline = pipeline;
	}

	void DMKRenderableComponent::addRenderableComponent(DMKRenderableComponent* component)
	{
		renderComponents.pushBack(component);
	}

	void DMKRenderableComponent::setLocation(Vector3F position)
	{
		this->position = position;
	}

	void DMKRenderableComponent::setBindingIndex(const UI32& index)
	{
		uniformDescription.destinationBinding = index;
	}
}
