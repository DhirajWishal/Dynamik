// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERABLE_COMPONENT_H
#define _DYNAMIK_RENDERABLE_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		11/06/2020
*/
#include "../Component.h"
#include "Core/Object/Resource/ShaderModule.h"
#include "Core/Object/Resource/Texture.h"
#include "GameLibrary/Camera/CameraModule.h"

namespace Dynamik
{
	/*
	 Mesh rendering pipelin
	 This defines which pipeline to use when rendering the mesh.
	 Custom pipelines should provide its own shader modules.
	*/
	enum class DMKBaseRenderingPipeline {
		DMK_BASE_RENDERING_PIPELINE_DEFAULT,
		DMK_BASE_RENDERING_PIPELINE_PBR,
		DMK_BASE_RENDERING_PIPELINE_LIGHT,
		DMK_BASE_RENDERING_PIPELINE_CUSTOM,
	};

	/*
	 Mesh rendering specifications
	 This defines how the mesh should be rendered.
	*/
	struct DMK_API DMKMeshRenderSpecifications {
		ARRAY<DMKShaderModule> shaderModules;
		DMKBaseRenderingPipeline basePipeline = DMKBaseRenderingPipeline::DMK_BASE_RENDERING_PIPELINE_CUSTOM;
	};

	/*
	 Dynamik Renderable Component
	 This contains all the necessary data required by a renderable component.
	*/
	class DMK_API DMKRenderableComponent : public DMKComponent {
	public:
		DMKRenderableComponent() {}
		virtual ~DMKRenderableComponent() {}

		virtual void addShaderModule(const DMKShaderModule& sModule);
		virtual void addTextureModule(DMKTexture* pTexture);
		virtual void setBaseRenderingPipeline(const DMKBaseRenderingPipeline& pipeline);

		/*
		 Add a renderable component which this component uses.
		*/
		virtual void addRenderableComponent(DMKRenderableComponent* component);
		virtual void setCameraModule(DMKCameraModule* cModule);

	public:		/* Constant methods */
		void setBindingIndex(const UI32& index);

	public:		/* Data Store */
		ARRAY<DMKShaderModule> shaderModules;
		ARRAY<DMKTexture*> textureModules;
		ARRAY<DMKRenderableComponent*> renderComponents;
		DMKUniformDescription uniformDescription;
		DMKCameraModule* cameraModule;
		DMKBaseRenderingPipeline basePipeline = DMKBaseRenderingPipeline::DMK_BASE_RENDERING_PIPELINE_CUSTOM;
	};
}

#endif // !_DYNAMIK_RENDERABLE_COMPONENT_H
