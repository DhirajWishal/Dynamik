// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RenderableComponent.h"

#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKRenderableComponent::addTextureModule(DMKTexture* pTexture)
	{
		DMKMaterial newMaterial;
		newMaterial.name = TEXT("DefaultTexture");
		newMaterial.addTexture(pTexture, MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		addMaterial(newMaterial);
		
	}

	void DMKRenderableComponent::addResourceRequest(const DMKResourceRequest& request)
	{
		resourceRequests.pushBack(request);
	}

	void DMKRenderableComponent::setResourceRequests(ARRAY<DMKResourceRequest> resourceRequests)
	{
		this->resourceRequests = resourceRequests;
	}

	ARRAY<DMKResourceRequest> DMKRenderableComponent::getResourceRequests() const
	{
		return resourceRequests;
	}
}
