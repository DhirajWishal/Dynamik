// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERABLE_COMPONENT_H
#define _DYNAMIK_RENDERABLE_COMPONENT_H

#include "Component.h"
#include "Core/Objects/Resources/ShaderModule.h"
#include "Core/Objects/Resources/MeshObject.h"
#include "GameLibrary/Camera/CameraModule.h"
#include "Core/Math/Quaternion.h"

namespace Dynamik
{
	/* Dynamik Resource Request */
	enum class DMK_API DMKResourceRequest {
		DMK_RESOURCE_REQUEST_BRDF_TABLE,
		DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE,
		DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE,
	};

	/*
	 Dynamik Renderable Component
	 This contains all the necessary data required by a renderable component.
	*/
	class DMK_API DMKRenderableComponent : public DMKComponent {
	public:
		DMKRenderableComponent() {}
		virtual ~DMKRenderableComponent() {}

		virtual void addTextureModule(DMKTexture* pTexture);

		void addResourceRequest(const DMKResourceRequest& request);
		void setResourceRequests(ARRAY<DMKResourceRequest> resourceRequests);
		ARRAY<DMKResourceRequest> getResourceRequests() const;

	public:		/* Materials */
		void addMaterial(const DMKMaterial& material) { materials.pushBack(material); }

		ARRAY<DMKMaterial> materials;

	public:		/* Data Store */
		ARRAY<DMKResourceRequest> resourceRequests;
		STRING name = TEXT("");
	};
}

#endif // !_DYNAMIK_RENDERABLE_COMPONENT_H
