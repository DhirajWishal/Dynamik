// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "CanvasEntity.h"

void DMKCanvasEntity::addShaderModule(const DMKShaderModule& sModule)
{
	shaders.push_back(sModule);
}

void DMKCanvasEntity::setShaderModules(std::vector<DMKShaderModule> sModules)
{
	shaders = std::move(sModules);
}

DMKShaderModule* DMKCanvasEntity::getShaderModule(I32 index)
{
	return &shaders.at(index);
}

std::vector<DMKShaderModule> DMKCanvasEntity::getShaders()
{
	return shaders;
}

void DMKCanvasEntity::createFrameMesh(const Vector3F& minimumBounds, const Vector3F& maximumBounds)
{
	/* Generate vertex data. */
	struct VertexCanvas {
		VertexCanvas() {}
		VertexCanvas(const Vector3F& position, const Vector2F& textureCoords) : position(position), textureCoord(textureCoords) {}

		Vector3F position = Vector3F(0.0f);
		Vector2F textureCoord = Vector2F(0.0f);
	};

	std::vector<VertexCanvas> vertexes;
	vertexes.push_back(VertexCanvas(minimumBounds, Vector2F(0)));
	vertexes.push_back(VertexCanvas(Vector3F(maximumBounds.x, maximumBounds.y, (maximumBounds.z + minimumBounds.z) / 2.0f), Vector2F(0.0f, 1.0f)));
	vertexes.push_back(VertexCanvas(Vector3F(minimumBounds.x, minimumBounds.y, (maximumBounds.z + minimumBounds.z) / 2.0f), Vector2F(1.0f, 0.0f)));
	vertexes.push_back(VertexCanvas(maximumBounds, Vector2F(1)));

	/* Generate index data. */
	std::vector<UI32> indexes = { 0, 1, 2, 1, 3, 2 };

	/* Generate vertex layout data. */
	DMKVertexLayout vLayout;
	vLayout.addAttribute(DMKVertexAttribute(DMKFormat::DMK_FORMAT_RGBA_32_SF32, 1, DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION));
	vLayout.addAttribute(DMKVertexAttribute(DMKFormat::DMK_FORMAT_RG_32_SF32, 1, DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0));

	/* Initialize the mesh object. */
	{
		/* Initialize vertex buffer. */
		frameMesh.getVertexBuffer().setLayout(vLayout);
		frameMesh.getVertexBuffer().initialize(vertexes.size());
		frameMesh.getVertexBuffer().setData(vertexes.data());

		/* Initialize index buffer. */
		frameMesh.getIndexBuffer().setIndexSize(sizeof(UI32));
		frameMesh.getIndexBuffer().initialize(indexes.size());
		frameMesh.getIndexBuffer().set(indexes.data(), indexes.size() * sizeof(UI32), 0);
	}
}

void DMKCanvasEntity::setFrameMesh(const DMKMeshObject& meshObject)
{
	frameMesh = meshObject;
}

DMKMeshObject* DMKCanvasEntity::getFrameMesh() const
{
	return Cast<DMKMeshObject*>(&frameMesh);
}
