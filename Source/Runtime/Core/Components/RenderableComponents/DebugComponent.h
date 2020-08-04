// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_DEBUG_COMPONENT_H
#define _DYNAMIK_DEBUG_COMPONENT_H

#include "../Component.h"
#include "Core/Objects/Resources/UniformBuffer.h"
#include "Core/Objects/Resources/VertexBuffer.h"
#include "Core/Objects/Resources/ShaderModule.h"
#include "Core/Objects/Resources/Material.h"

namespace Dynamik
{
	/* Dynamik Debug Component Usage */
	enum DMKDebugComponentUsage {
		DMK_DEBUG_COMPONENT_USAGE_RENDERING = BIT_SHIFT(0),
		DMK_DEBUG_COMPONENT_USAGE_AUDIO = BIT_SHIFT(1),
		DMK_DEBUG_COMPONENT_USAGE_PHYSICS = BIT_SHIFT(2),
	};

	/*
	 Dynamik Debug Component
	 This object is user defined and can be used to debug rendering, audio, physics and other systems.

	 Additionally, vertex buffers (in the renderer backend layer) will be updated on every frame.
	*/
	class DMK_API DMKDebugComponent : public DMKComponent {
	public:
		DMKDebugComponent(DMKDebugComponentUsage usage = DMKDebugComponentUsage::DMK_DEBUG_COMPONENT_USAGE_RENDERING) : usage(usage) {}
		virtual ~DMKDebugComponent() {}

		/*
		 Initialize the component.
		 This function must be called by the user.
		*/
		virtual void initialize() {}

		/*
		 Set uniform buffer.

		 @param buffer: The new uniform buffer.
		*/
		void setUniformBuffer(const DMKUniformBuffer& buffer);

		/*
		 Get the uniform buffer.
		*/
		DMKUniformBuffer& getUniformBuffer();

		/*
		 Set vertex buffer.

		 @param buffer: The new vertex buffer.
		*/
		void setVertexBuffer(const DMKVertexBuffer& buffer);

		/*
		 Get the vertex buffer.
		*/
		DMKVertexBuffer& getVertexBuffer();

		/*
		 Set the index buffer.

		 @param buffer: The new index buffer.
		*/
		void setIndexBuffer(const ARRAY<UI32>& buffer);

		/*
		 Get the index buffer.
		*/
		ARRAY<UI32>& getIndexBuffer();

		/*
		 Add a material to the store.

		 @param material: The material to be added.
		*/
		void addMaterial(const DMKMaterial& material);

		/*
		 Set a new material store.

		 @param materials: The new materials.
		*/
		void setMaterials(const ARRAY<DMKMaterial>& materials);

		/*
		 Get a material from the store.

		 @param index: The material index.
		*/
		DMKMaterial& getMaterial(const UI64& index);

		/*
		 Get the whole material store.
		*/
		ARRAY<DMKMaterial>& getMaterials();

		/*
		 Add a shader.

		 @param module: The new shader module.
		*/
		void addShader(const DMKShaderModule& module);

		/*
		 Set the shader store.

		 @param modules: The shader module store.
		*/
		void setShaders(const ARRAY<DMKShaderModule>& modules);

		/*
		 Get a shader from the store.

		 @param index: Index of the shader.
		*/
		DMKShaderModule& getShader(const UI64& index);

		/*
		 Get the shader store.
		*/
		ARRAY<DMKShaderModule>& getShaders();

	public:
		DMKUniformBuffer uniformBuffer;
		DMKVertexBuffer vertexBuffer;
		ARRAY<UI32> indexBuffer;
		ARRAY<DMKMaterial> materials;
		ARRAY<DMKShaderModule> shaders;
		DMKDebugComponentUsage usage = DMKDebugComponentUsage::DMK_DEBUG_COMPONENT_USAGE_RENDERING;
	};
}

#endif // !_DYNAMIK_DEBUG_COMPONENT_H
