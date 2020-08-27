// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshFactory.h"

#include "Importer/Asset/MeshImporter.h"
#include "Importer/Asset/AnimationImporter.h"
#include "Core/Utilities/TextureFactory.h"

DMKMeshFactory DMKMeshFactory::instance;

void DMKMeshFactory::setWorkingDirectory(const STRING& path)
{
	instance.workingDirectory = path;
}

DMKMeshObject DMKMeshFactory::createBasicTriangle()
{
	DMKMeshObject component;

	struct TempVertex {
		TempVertex() {}
		TempVertex(const Vector3F& position, const Vector3F& color) : position(position), color(color) {}
		~TempVertex() {}

		Vector3F position;
		Vector3F color;
	};

	ARRAY<TempVertex> vertexes = {
		TempVertex({ 0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }),
		TempVertex({ 0.5f,  -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }),
		TempVertex({ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }),
	};

	ARRAY<UI32> indexes = {
		0, 1, 2
	};

	DMKVertexLayout vertexLayout;
	DMKVertexAttribute vertexAttribute;
	vertexAttribute.dataCount = 1;
	vertexAttribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;

	vertexAttribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	vertexLayout.attributes.pushBack(vertexAttribute);

	vertexAttribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
	vertexLayout.attributes.pushBack(vertexAttribute);

	component.vertexBuffer.initialize(vertexes.size(), vertexLayout);
	component.vertexBuffer.setData(vertexes.data());

	return component;
}

DMKMeshObject DMKMeshFactory::loadFromFile(const STRING& file, const DMKVertexLayout& vertexLayout)
{
	return DMKMeshImporter::loadMeshes(file, vertexLayout)[0];
}

DMKMeshObject DMKMeshFactory::createDefault(const STRING& path)
{
	DMKMeshObject component = DMKMeshImporter::loadMeshes(path, DMKVertexLayout::createBasicIBL())[0];

	return component;
}

DMKMeshObject DMKMeshFactory::createCube()
{
	DMKMeshObject component = DMKMeshImporter::loadMeshes(instance.workingDirectory + "/Runtime/Assets/Models/Cube/Cube.obj", DMKVertexLayout::createBasic())[0];

	return component;
}

DMKMeshObject DMKMeshFactory::createSkyBox(ARRAY<STRING> textureFiles)
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataCount = 1;
	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	layout.attributes.pushBack(attribute);

	DMKMeshObject component = DMKMeshImporter::loadMeshes(instance.workingDirectory + "/Runtime/Assets/Models/SkyBox/SkySphere.obj", layout)[0];

	component.getMaterial().addTexture(DMKTextureFactory::createCubeMap(textureFiles), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);

	return component;
}

DMKMeshObject DMKMeshFactory::loadAnimatedMesh(const STRING& file)
{
	return DMKMeshObject();
}

DMKMeshObject DMKMeshFactory::loadStaticModel(const STRING& file, Vector3F position, Vector3F scale)
{
	auto meshes = DMKMeshImporter::loadMeshes(file, DMKVertexLayout::createBasic());
	DMKMeshObject newModel;

	for (auto mesh : meshes)
	{
	}

	return newModel;
}

ARRAY<DMKMeshObject> DMKMeshFactory::loadMeshes(const STRING& file, DMKVertexLayout vertexLayout)
{
	return  DMKMeshImporter::loadMeshes(file, vertexLayout);
}
