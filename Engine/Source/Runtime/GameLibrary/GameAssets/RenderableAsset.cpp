#include "dmkafx.h"
#include "RenderableAsset.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKRenderableAsset::initialize()
	{
	}

	void DMKRenderableAsset::onUpdate(const DMKEventBuffer& eventBuffer)
	{
		for (auto mesh : meshComponents)
		{

		}
	}

	POINTER<DMKMeshComponent> DMKRenderableAsset::createMeshComponent(STRING path, ARRAY<DMKUniformDescription> uniformDescriptors)
	{
		auto mesh = DMKMeshImporter::loadMeshes(path);

		for (UI32 index = 0; index < mesh.size(); index++)
		{
			for (auto _description : uniformDescriptors)
			{
				DMKUniformBufferObject _ubo;
				_ubo.myDescription = _description;
				mesh[index].uniformBUfferObjects.pushBack(_ubo);
			}
		}

		meshComponents.insert(mesh);

		return meshComponents.location(-1);
	}

	POINTER<DMKMeshComponent> DMKRenderableAsset::createMeshComponent(ARRAY<DMKVertexObject> vertexData, ARRAY<UI32> indexData, DMKVertexBufferDescriptor vertexDescription, ARRAY<DMKUniformDescription> uniformDescriptors)
	{
		DMKMeshComponent _mesh;
		_mesh.rawVertexBufferObject = vertexData;
		_mesh.vertexDescriptor = vertexDescription;
		_mesh.indexBufferObject = indexData;
		_mesh.indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;
		for (auto _description : uniformDescriptors)
		{
			DMKUniformBufferObject _object;
			_object.myDescription = _description;
			_mesh.uniformBUfferObjects.pushBack(_object);
		}

		meshComponents.pushBack(_mesh);

		return meshComponents.location(-1);
	}

	DMKUniformDescription DMKRenderableAsset::createUniformMVP()
	{
		DMKUniformDescription _description;
		_description.destinationBinding = 1;
		_description.offset = 0;
		_description.shaderLocation = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
		_description.type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;

		DMKUniformAttribute _attribute1;
		_attribute1.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL;
		_attribute1.dataCount = 1;
		_attribute1.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute1);

		DMKUniformAttribute _attribute2;
		_attribute2.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_VIEW;
		_attribute2.dataCount = 1;
		_attribute2.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute2);

		DMKUniformAttribute _attribute3;
		_attribute3.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_PROJECTION;
		_attribute3.dataCount = 1;
		_attribute3.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute3);

		return _description;
	}
}
