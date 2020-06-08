#pragma once
#ifndef _DYNAMIK_RESOURCE_PRIMITIVES_H
#define _DYNAMIK_RESOURCE_PRIMITIVES_H

/*
 This file contains all the primitive resources in their virtual form (Vertex, Shader, Uniform).

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Math/MathTypes.h"
#include "Types/Array.h"
#include "ShaderModule.h"

namespace Dynamik
{
	/* Vertex */
	/* TEMPLATED CONTAINER
	 Dynamik Engine supports multiple sizes of vertex bone information types. These types are based on the number
	 of boneIDs, boneWeights the container supports. These count ranges are: 8, 16, 32, 65, 256, 512 and 1024.
	*/
	template<const UI32 BoneCount = 8>
	struct  DMK_API VertexBoneInformation {
		/*
		 Add a bone to the container.

		 @param boneID: ID of the bone.
		 @param boneWeight:	Weight of that bone ID.
		*/
		void addBone(UI32 boneID, F32 boneWeight)
		{
			for (UI32 _itr = 0; _itr < BoneCount; _itr++)
			{
				if (boneWeights[_itr] == 0.0f)
				{
					boneIDs[_itr] = boneID;
					boneWeights[_itr] = boneWeight;

					return;
				}
			}
		}

		UI32 boneIDs[BoneCount] = { 0 };
		F32 boneWeights[BoneCount] = { 0.0f };
	};

	/*
	 This Structure contains all the possible vertex data in a mesh. Later when submitting the data, each
	 vertex gets packed into a pre allocated space using the vertex attributes.
	*/
	struct DMK_API DMKVertexObject {
		/* Bone information container */
		POINTER<VertexBoneInformation<8U>> boneInformation;

		VEC3F position;
		VEC3F color;
		VEC3F textureCoord;
		VEC3F uvCoord;
		VEC3F normal;
		F32 integrity = 0.0f;   /* For the Dynamik Destruction Engine */
	};

	/* Vertex attribute types */
	enum class DMK_API DMKVertexAttributeType {
		DMK_VERTEX_ATTRIBUTE_TYPE_POSITION,                 /* Position coordinates */
		DMK_VERTEX_ATTRIBUTE_TYPE_COLOR,                    /* Color coordinates */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES,      /* Texture coordinates */
		DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES,           /* UV coordinates */
		DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL,                   /* Normal vectors */
		DMK_VERTEX_ATTRIBUTE_TYPE_SINTEGRITY,               /* Integrity value */
		DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID,                  /* Bone IDs */
		DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT,              /* Bone Weights */
		DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM                    /* Custom */
	};

	/* Dynamik Vertex Attribute */
	struct DMK_API DMKVertexAttribute {
		DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		DMKVertexAttributeType attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
		UI32 dataCount = 1;     /* Number of elements of data which is sent. Used for sending arrays. */
	};

	/* This contains all the vertex buffer attributes */
	class DMK_API DMKVertexBufferDescriptor {
	public:
		DMKVertexBufferDescriptor() {}
		~DMKVertexBufferDescriptor() {}

		/* Get the size of the vertex using the attributes */
		UI32 getVertexSize();

		/* Vertex attributes */
		ARRAY<DMKVertexAttribute> attributes;
	};

	/* Constant Block */
	/* Dynamik Constant Attribute */
	struct DMK_API DMKConstantAttribute {
		DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_F32;
		UI64 dataCount = 1;
	};

	/* Dynamik Constant Block Descriptor */
	struct DMK_API DMKConstantBlockDescription {
		ARRAY<DMKConstantAttribute> attributes;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
		UI32 offset = 0;

		/* Block size */
		UI64 getBlockSize();
	};

	/* Uniform */
	/* Dynamik Uniform Type */
	enum class DMK_API DMKUniformType {
		DMK_UNIFORM_TYPE_UNIFORM_BUFFER,
		DMK_UNIFORM_TYPE_STORAGE_BUFFER,
		DMK_UNIFORM_TYPE_UNIFORM_BUFFER_DYNAMIC,
		DMK_UNIFORM_TYPE_STORAGE_BUFFER_DYNAMIC,
		DMK_UNIFORM_TYPE_UNIFORM_TEXEL_BUFFER,
		DMK_UNIFORM_TYPE_STORAGE_TEXEL_BUFFER,
		DMK_UNIFORM_TYPE_INPUT_ATTACHMENT,
		DMK_UNIFORM_TYPE_STORAGE_IMAGE,
		DMK_UNIFORM_TYPE_CONSTANT,
		DMK_UNIFORM_TYPE_SAMPLER_2D,
		DMK_UNIFORM_TYPE_SAMPLER_CUBE,
		DMK_UNIFORM_TYPE_SAMPLER_2D_ARRAY,
		DMK_UNIFORM_TYPE_SAMPLER_CUBE_ARRAY,
		DMK_UNIFORM_TYPE_ACCELERATION_STRUCTURE,
	};

	/* Dynamik Uniform Attribute Types */
	enum class DMK_API DMKUniformAttributeType {
		DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL,
		DMK_UNIFORM_ATTRIBUTE_TYPE_VIEW,
		DMK_UNIFORM_ATTRIBUTE_TYPE_PROJECTION,
		DMK_UNIFORM_ATTRIBUTE_TYPE_CUSTOM
	};

	/* Dynamik Uniform Buffer Usage */
	enum class DMK_API DMKUniformBufferUsage {
		DMK_UNIFORM_BUFFER_USAGE_CAMERA,
		DMK_UNIFORM_BUFFER_USAGE_SAMPLER,
		DMK_UNIFORM_BUFFER_USAGE_CUSTOM,
	};

	/* Dynamik Uniform Attribute */
	struct DMK_API DMKUniformAttribute {
		DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		DMKUniformAttributeType attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL;
		UI32 dataCount = 1;     /* Number of data elements that is sent to the shader. Used when sending an array. */
	};

	/*
	 Dynamik Uniform Description
	 This object contains all the necessary information to create a uniform buffer object in the Dynamik Engine.
	*/
	struct DMK_API DMKUniformDescription {
		ARRAY<DMKUniformAttribute> attributes;
		DMKUniformType type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;
		DMKShaderLocation shaderLocation = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
		DMKUniformBufferUsage usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_CUSTOM;
		UI32 destinationBinding = 0;
		UI32 offset = 0;

		/* Get the total byte size of the uniform buffer object. */
		UI64 getUniformSize();
	};

	/* Dynamik Uniform Descriptor */
	class DMK_API DMKUniformBufferDescriptor {
	public:
		DMKUniformBufferDescriptor() {}
		~DMKUniformBufferDescriptor() {}

		/* Buffer object contaienr */
		ARRAY<DMKUniformDescription> uniformBufferObjects;

		/* ID operator */
		I64 operator()();
	};

	/*
	 Dynamik Uniform Buffer Object
	 Uniform data are passed to the Dynamik Engine using this object.
	 */
	class DMK_API DMKUniformBufferObject {
	public:
		DMKUniformBufferObject() {}
		~DMKUniformBufferObject();

		/* Initialize the object */
		void initialize(const DMKUniformDescription& description);

		/*
		 Add data to the uniform buffer object.

		 @param data: The data to be added to the buffer.
		 @param byteSize: Size of the added data.
		 @param location: The location to which the data is bound. This location corresponds to the uniform
						  binding.
		 @param arrayIndex: Index to which the data are bound in the array. If the buffer element at the
							location does not contain an array, the index is kept 0.
		*/
		void setData(const VPTR& data, const UI32& byteSize, const UI32& location, const UI32& arrayIndex = 0U);

		/* Clear all the stored values in the buffer */
		void clear();

	private:	/* Private Data Store */
		VPTR uniformBufferStorage = nullptr;
		POINTER<BYTE> nextPointer = uniformBufferStorage;

	public:		/* Public Data */
		DMKUniformDescription myDescription;

	public:		/* Static Utility Functions */
		/*
		 Create a basic Camera uniform buffer object.
		*/
		static DMKUniformDescription createUniformCamera(UI32 binding = 0, DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX);

		/*
		 Create a basic model uniform buffer object.
		*/
		static DMKUniformDescription createUniformModel(UI32 binding = 0, DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX);
	};
}

#endif // !_DYNAMIK_RESOURCE_PRIMITIVES_H
