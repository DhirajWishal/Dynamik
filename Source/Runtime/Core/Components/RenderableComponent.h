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
	 Dynamik Render Cluster
	 The rendering engine handles meshes in clusters. One cluster gets one pipeline and a cluster contains one or 
	 multiple mesh objects.
	*/
	struct DMK_API DMKRenderCluster {
		ARRAY<DMKMeshObject> meshObjects;
		ARRAY<DMKShaderModule> shaders;
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

		virtual void translate(const MAT4& mat, const VEC3& vec) {}
		virtual void rotate(const VEC3& direction, const F32& radians) {}

		void addResourceRequest(const DMKResourceRequest& request);
		void setResourceRequests(ARRAY<DMKResourceRequest> resourceRequests);
		ARRAY<DMKResourceRequest> getResourceRequests() const;

		/*
		 Get a uniform stored in a given shader index.
		 The shader index is in the order of shader submission.

		 @param shaderIndex: The index of the shader.
		 @param unuformIndex: The index of the uniform in the shader.
		*/
		DMKUniformBuffer& getUniform(I64 shaderIndex = 0, I64 uniformIndex = 0);

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
		ARRAY<DMKResourceRequest> resourceRequests;

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
	};
}

#endif // !_DYNAMIK_RENDERABLE_COMPONENT_H
