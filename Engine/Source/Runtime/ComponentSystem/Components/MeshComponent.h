#pragma once
#ifndef _DYNAMIK_MESH_COMPONENT_H
#define _DYNAMIK_MESH_COMPONENT_H

/*
 Dynamik Mesh Component.
 This component contains all the necessary variables to store all the available mesh data of an imported
 mesh.
 This also contains all the functionalities to manipulate a mesh object.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "../Component.h"
#include "Core/Object/Resource/ShaderModule.h"
#include "Object/Resource/Textures/TextureFactory.h"

namespace Dynamik
{
	/*
	 Usage of the mesh component
	*/
	enum class DMKMeshComponentUsage {
		DMK_MESH_COMPONENT_USAGE_STATIC,
		DMK_MESH_COMPONENT_USAGE_ANIMATED,
		DMK_MESH_COMPONENT_USAGE_SKYBOX,
	};

	/*
	 Mesh rendering pipelin
	 This defines which pipeline to use when rendering the mesh.
	 Custom pipelines should provide its own shader modules.
	*/
	enum class DMKMeshRenderingPipeline {
		DMK_MESH_RENDERING_PIPELINE_DEFAULT,
		DMK_MESH_RENDERING_PIPELINE_PBR,
		DMK_MESH_RENDERING_PIPELINE_LIGHT,
		DMK_MESH_RENDERING_PIPELINE_CUSTOM,
	};

	/*
	 Mesh rendering specifications
	 This defines how the mesh should be rendered.
	*/
	struct DMK_API DMKMeshRenderSpecifications {
		ARRAY<DMKShaderModule> shaderModules;
		DMKMeshRenderingPipeline basePipeline = DMKMeshRenderingPipeline::DMK_MESH_RENDERING_PIPELINE_CUSTOM;
	};

	/*
	 Mesh Component for the Dynamik Engine.
	*/
	class DMK_API DMKMeshComponent : public DMKComponent {
	public:
		DMKMeshComponent() {}
		DMKMeshComponent(const DMKMeshComponentUsage& usage) : usage(usage) {}
		DMKMeshComponent(const DMKMeshComponentUsage& usage, const DMKVertexBufferDescriptor& descriptor, const DMKDataType& type)
			: usage(usage), vertexDescriptor(descriptor), indexBufferType(type) {}
		~DMKMeshComponent() {}

		/* Get the total byte size of the vertex buffer object */
		UI32 getVertexBufferObjectByteSize();

		/* Get the total byte size of the index buffer object */
		UI32 getIndexBufferObjectByteSize();

		/*
		 Pack all vertex data into a location.

		 @warn: The pre allocated memory location must be allocated to fit the whole vertex buffer object.
				To ensure this, use getVertexBufferObjectByteSize() to allocate the buffer percisely.
		*/
		void packData(VPTR location);

		void setMatrix(const MAT4F& matrix);
		MAT4F getMatrix();

	public:		/* Public Data Store */
		ARRAY<DMKVertexObject> rawVertexBufferObject;

		DMKMeshRenderSpecifications renderSpecifications;

		ARRAY<DMKUniformBufferObject> uniformBufferObjects;
		ARRAY<UI32> indexBufferObject;
		POINTER<DMKTexture> texture;

	public:		/* Matrix */
		MAT4F modelMatrix;

	public:		/* Descriptors */
		DMKVertexBufferDescriptor vertexDescriptor;
		DMKDataType indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;
		DMKMeshComponentUsage usage = DMKMeshComponentUsage::DMK_MESH_COMPONENT_USAGE_STATIC;
		DMKMeshRenderingPipeline pipeline = DMKMeshRenderingPipeline::DMK_MESH_RENDERING_PIPELINE_DEFAULT;

	public:		/* Static Utility Functions */
		/*
		 Create a new mesh component and add it to the mesh store. Return the address of the last element
		 of the store.
		 If the specified path contain more than one mesh, all of it will be loaded and added to the store.

		 @param path: Path to the file tp be imported.
		 @param UniformDescriptors:	Descriptors to the uniform buffers the mesh contains.
		*/
		static ARRAY<DMKMeshComponent> create(STRING path, ARRAY<DMKUniformDescription> uniformDescriptors);

		/*
		 Create a new mesh component and add it to the mesh store. Return the address of the last element
		 of the store.

		 @param vertexData:	The vertex data of the mesh.
		 @param indexData: Index data of the mesh.
		 @param vertexDescription: Vertex description of the mesh.
		 @param UniformDescriptors:	Descriptors to the uniform buffers the mesh contains.
		*/
		static ARRAY<DMKMeshComponent> create(ARRAY<DMKVertexObject> vertexData, ARRAY<UI32> indexData, DMKVertexBufferDescriptor vertexDescription, ARRAY<DMKUniformDescription> uniformDescriptors);
	};
}

#endif // !_DYNAMIK_MESH_COMPONENT_H
