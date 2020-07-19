// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERABLE_COMPONENT_H
#define _DYNAMIK_RENDERABLE_COMPONENT_H

#include "Component.h"
#include "Core/Objects/Resources/ShaderModule.h"
#include "Core/Objects/Resources/Material.h"
#include "GameLibrary/Camera/CameraModule.h"
#include "Core/Math/Quaternion.h"

namespace Dynamik
{
	/*
	 Mesh rendering pipeline
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
		virtual void clearShaderModules();

		virtual void addTextureModule(DMKTexture* pTexture);
		virtual void setBaseRenderingPipeline(const DMKBaseRenderingPipeline& pipeline);

		virtual void translate(const MAT4& mat, const VEC3& vec) {}
		virtual void rotate(const VEC3& direction, const F32& radians) {}

		/*
		 Add a renderable component which this component uses.
		*/
		virtual void addRenderableComponent(DMKRenderableComponent* component);

		/*
		 Set a rotation to the instance.
		*/
		virtual void setRotation(Quaternion rotation);

		/*
		 Get rotation of the instance.
		*/
		Quaternion getRotation() const { return rotation; }

		/*
		 Add a location to the component.
		*/
		virtual void setPosition(Vector3F position);

		/*
		 Get the position of the instance.
		*/
		Vector3F getPosition() const { return position; }

		/*
		 Add a scale to the component.
		*/
		virtual void setScale(Vector3F scale);

		/*
		 Get the scale of the instance.
		*/
		Vector3F getScale() const { return scale; }

	public:		/* Constant methods */
		void setBindingIndex(const UI32& index);

	public:		/* Materials */
		void addMaterial(const DMKMaterial& material) { materials.pushBack(material); }

		ARRAY<DMKMaterial> materials;

	public:		/* Data Store */
		ARRAY<DMKShaderModule> shaderModules;
		ARRAY<DMKRenderableComponent*> renderComponents;

		/*
		 Rotation of the instance.
		*/
		Quaternion rotation;

		/*
		 Position of one instance.
		*/
		Vector3F position;

		/*
		 Scale of the instance.
		*/
		Vector3F scale;

		DMKUniformDescription uniformDescription;
		DMKBaseRenderingPipeline basePipeline = DMKBaseRenderingPipeline::DMK_BASE_RENDERING_PIPELINE_CUSTOM;
	};
}

#endif // !_DYNAMIK_RENDERABLE_COMPONENT_H
