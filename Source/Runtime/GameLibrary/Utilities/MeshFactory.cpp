// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshFactory.h"

#include "Importer/Asset/MeshImporter.h"
#include "Core/Objects/Resource/TextureFactory.h"

namespace Dynamik
{
	DMKMeshFactory DMKMeshFactory::instance;

	void DMKMeshFactory::setWorkingDirectory(const STRING& path)
	{
		instance.workingDirectory = path;
	}

	DMKMeshComponent DMKMeshFactory::createBasicTriangle()
	{
		DMKMeshComponent component;

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

		component.indexBuffer = indexes;
		component.indexCount = indexes.size();
		component.vertexBuffer = StaticAllocator<BYTE>::allocate(vertexes.typeSize() * vertexes.size());
		DMKMemoryFunctions::moveData(component.vertexBuffer, vertexes.data(), vertexes.typeSize() * vertexes.size());
		component.vertexCount = vertexes.size();

		DMKVertexLayout vertexLayout;
		DMKVertexAttribute vertexAttribute;
		vertexAttribute.dataCount = 1;
		vertexAttribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;

		vertexAttribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
		vertexLayout.attributes.pushBack(vertexAttribute);

		vertexAttribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
		vertexLayout.attributes.pushBack(vertexAttribute);

		component.vertexLayout = vertexLayout;

		component.addShaderModule(DMKShaderFactory::createModule(instance.workingDirectory + "/Runtime/Assets/Shaders/triangle-vert-3D.spv", DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		component.addShaderModule(DMKShaderFactory::createModule(instance.workingDirectory + "/Runtime/Assets/Shaders/triangle-frag-3D.spv", DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

		return component;
	}

	DMKMeshComponent DMKMeshFactory::createDefault(const STRING& path)
	{
		DMKMeshComponent component = DMKMeshImporter::loadMeshes(path, DMKVertexLayout::createBasic())[0];

		component.addShaderModule(DMKShaderFactory::createModule(instance.workingDirectory + "/Runtime/Assets/Shaders/3D/vert.spv", DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		component.addShaderModule(DMKShaderFactory::createModule(instance.workingDirectory + "/Runtime/Assets/Shaders/3D/frag.spv", DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

		return component;
	}
	
	DMKMeshComponent DMKMeshFactory::createCube()
	{
		DMKMeshComponent component = DMKMeshImporter::loadMeshes(instance.workingDirectory + "/Runtime/Assets/Models/Cube/Cube.obj", DMKVertexLayout::createBasic())[0];

		return component;
	}
	
	DMKMeshComponent DMKMeshFactory::createSkyBox(ARRAY<STRING> textureFiles)
	{
		DMKVertexLayout layout;
		DMKVertexAttribute attribute;
		attribute.dataCount = 1;
		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		layout.attributes.pushBack(attribute);

		DMKMeshComponent component = DMKMeshImporter::loadMeshes(instance.workingDirectory + "/Runtime/Assets/Models/SkyBox/SkySphere.obj", layout)[0];

		component.addShaderModule(DMKShaderFactory::createModule(instance.workingDirectory + "/Runtime/Assets/Shaders/SkyBox/vert.spv", DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		component.addShaderModule(DMKShaderFactory::createModule(instance.workingDirectory + "/Runtime/Assets/Shaders/SkyBox/frag.spv", DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		
		component.addTextureModule(DMKTextureFactory::createCubeMap(textureFiles));

		return component;
	}
}
