// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshObject.h"

namespace Dynamik
{
	void DMKMeshObject::setName(const STRING& name)
	{
		this->name = name;
	}

	const STRING& DMKMeshObject::getName() const
	{
		return name;
	}

	void DMKMeshObject::clearVertexAndIndexBuffers()
	{
		/* Clear vertex buffer */
		vertexBuffer.clear();

		/* Clear index buffer */
		indexBuffer.clear();
	}

	void DMKMeshObject::loadVertexDataFromPointer(const VPTR address)
	{
		vertexBuffer.addData(address, vertexBuffer.byteSize(), 0);
	}
	
	void DMKMeshObject::loadIndexDataFromPointer(const VPTR address)
	{
		indexBuffer.set(address, indexBuffer.size(), 0);
	}

	void DMKMeshObject::setVertexBuffer(const DMKVertexBuffer& vertexBuffer)
	{
		this->vertexBuffer = vertexBuffer;
	}

	void DMKMeshObject::setVertexLayout(const DMKVertexLayout& layout)
	{
		vertexBuffer.setLayout(layout);
	}

	DMKVertexBuffer& DMKMeshObject::getVertexBuffer()
	{
		return vertexBuffer;
	}

	void DMKMeshObject::setIndexBuffer(const DMKIndexBuffer& indexBuffer)
	{
		this->indexBuffer = indexBuffer;
	}

	void DMKMeshObject::addIndex(const UI32& index)
	{
		indexBuffer.add(index);
	}

	DMKIndexBuffer& DMKMeshObject::getIndexBuffer()
	{
		return indexBuffer;
	}

	void DMKMeshObject::addUniformBuffer(const DMKUniformBuffer& buffer)
	{
		uniformBuffers.pushBack(buffer);
	}

	void DMKMeshObject::setUniformBuffers(const ARRAY<DMKUniformBuffer>& buffers)
	{
		uniformBuffers = buffers;
	}

	DMKUniformBuffer& DMKMeshObject::getUniformBuffer(I64 index)
	{
		return uniformBuffers[index];
	}

	ARRAY<DMKUniformBuffer>& DMKMeshObject::getUniformBuffers()
	{
		return uniformBuffers;
	}

	void DMKMeshObject::setMaterial(const DMKMaterial& material)
	{
		this->material = material;
	}

	DMKMaterial& DMKMeshObject::getMaterial()
	{
		return material;
	}
	
	void DMKMeshObject::setRenderSpecification(const DMKMeshRenderSpecification& specification)
	{
		this->renderSpecification = specification;
	}
	
	DMKMeshRenderSpecification& DMKMeshObject::getRenderSpecification() const
	{
		return Cast<DMKMeshRenderSpecification&>(this->renderSpecification);
	}
}