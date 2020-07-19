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
		DMKMaterial newMaterial;
		newMaterial.addTexture(pTexture, MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);

		addMaterial(newMaterial);
	}

	void DMKRenderableComponent::setBaseRenderingPipeline(const DMKBaseRenderingPipeline& pipeline)
	{
		basePipeline = pipeline;
	}

	void DMKRenderableComponent::addRenderableComponent(DMKRenderableComponent* component)
	{
		renderComponents.pushBack(component);
	}

	void DMKRenderableComponent::setRotation(Quaternion rotation)
	{
		this->rotation = rotation;
	}

	void DMKRenderableComponent::setPosition(Vector3F position)
	{
		this->position = position;
	}

	void DMKRenderableComponent::setScale(Vector3F scale)
	{
		this->scale = scale;
	}

	void DMKRenderableComponent::setBindingIndex(const UI32& index)
	{
		uniformDescription.destinationBinding = index;
	}
}
