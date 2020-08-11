// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_OBJECT_H
#define _DYNAMIK_MESH_OBJECT_H

#include "Material.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"

namespace Dynamik
{
	/*
	 Dynamik Mesh Render Specification
	 This describes how a mesh object should be rendered.
	*/
	struct DMK_API DMKMeshRenderSpecification {
		ARRAY<DMKShaderModule> shaders;
	};

	/*
	 Dynamik Mesh Object
	 This object stores data of a single mesh.
	*/
	class DMK_API DMKMeshObject {
	public:
		DMKMeshObject() = default;
		~DMKMeshObject() = default;

	public:
		/*
		 Set the name of the mesh object. 

		 @param name: The name of the mesh.
		*/
		void setName(const STRING& name);

		/*
		 Get the name of the mesh object.
		*/
		const STRING& getName() const;

		/* The name of the mesh object. */
		STRING name = TEXT("");

	public:
		/*
		 Unload/ clear all the data stored in the vertex and index buffers. This helps in reducing memory usage.
		 This function must be called after submitting all the required data to the GPU.
		*/
		void clearVertexAndIndexBuffers();

		/*
		 Load vertex data from an address. 
		 This method will only work if the vertex buffer is already initialized with the right allocation. This method 
		 is used to load data back from the GPU.

		 @param address: The address of the data block.
		*/
		void loadVertexDataFromPointer(const VPTR address);

		/*
		 Load index data from an address. 
		 This method will only work if the index buffer is already initialized with the right allocation. This method 
		 is used to load data back from the GPU.

		 @param address: The address of the data block.
		*/
		void loadIndexDataFromPointer(const VPTR address);

	public:
		/*
		 Set a the vertex buffer of the current mesh object.

		 @param vertexBuffer: The vertex buffer to be set.
		*/
		void setVertexBuffer(const DMKVertexBuffer& vertexBuffer);

		/*
		 Set the vertex layout of the current vertex buffer. 
		 A vertex layout needs to be set before loading data to the vertex buffer. 

		 @param layout: The vertex layout.
		*/
		void setVertexLayout(const DMKVertexLayout& layout);

		/*
		 Get the vertex buffer stored in the current mesh object.
		*/
		DMKVertexBuffer& getVertexBuffer();

		/* Vertex Buffer */
		DMKVertexBuffer vertexBuffer = {};

	public:
		/* 
		 Set an index buffer to the mesh object.

		 @param indexBuffer: The index buffer to be set.
		*/
		void setIndexBuffer(const DMKIndexBuffer& indexBuffer);

		/*
		 Add an index to the index buffer.

		 @param index: The index to be added.
		*/
		void addIndex(const UI32& index);

		/*
		 Get the current index buffer.
		*/
		DMKIndexBuffer& getIndexBuffer();

		/* Index Buffer */
		DMKIndexBuffer indexBuffer = {};

	public:
		/*
		 Add a uniform buffer to the mesh object.

		 @param buffer: The uniform buffer to be added.
		*/
		void addUniformBuffer(const DMKUniformBuffer& buffer);

		/*
		 Set all the uniform buffers of the mesh object.

		 @param buffers: The array of uniform buffers.
		*/
		void setUniformBuffers(const ARRAY<DMKUniformBuffer>& buffers);

		/*
		 Get a uniform buffer from a given index.

		 @param index: The index of the uniform buffer.
		*/
		DMKUniformBuffer& getUniformBuffer(I64 index);

		/*
		 Get all the uniform buffers stored in the mesh object.
		*/
		ARRAY<DMKUniformBuffer>& getUniformBuffers();

		/* Uniform Buffers */
		ARRAY<DMKUniformBuffer> uniformBuffers = {};

		public:
		/*
		 Set a material to the current mesh object.

		 @param material: The material to be set.
		*/
		void setMaterial(const DMKMaterial& material);

		/*
		 Get the current material.
		*/
		DMKMaterial& getMaterial();

		/* Material */
		DMKMaterial material = {};
	};
}

#endif // !_DYNAMIK_MESH_OBJECT_H
