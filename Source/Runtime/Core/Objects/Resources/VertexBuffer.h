// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VERTEX_BUFFER_H
#define _DYNAMIK_VERTEX_BUFFER_H

#include "Core/Types/DataTypes.h"
#include "ShaderModule.h"

namespace Dynamik
{
	/* Shader input attribute types */
	enum class DMK_API DMKVertexAttributeType {
		DMK_VERTEX_ATTRIBUTE_TYPE_POSITION,						/* Position coordinates */
		DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL,						/* Normal vectors */
		DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0,						/* Color coordinates 0 */
		DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_1,						/* Color coordinates 1 */
		DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_2,						/* Color coordinates 2 */
		DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_3,						/* Color coordinates 3 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0,		/* Texture coordinates 0 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_1,		/* Texture coordinates 1 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_2,		/* Texture coordinates 2 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_3,		/* Texture coordinates 3 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_4,		/* Texture coordinates 4 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_5,		/* Texture coordinates 5 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_6,		/* Texture coordinates 6 */
		DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_7,		/* Texture coordinates 7 */
		DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES,				/* UV coordinates */
		DMK_VERTEX_ATTRIBUTE_TYPE_TANGENT,						/* Tangents */
		DMK_VERTEX_ATTRIBUTE_TYPE_BITANGENT,					/* Bi tangents */
		DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY,					/* Integrity value */
		DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID,						/* Bone IDs */
		DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT,					/* Bone Weights */
		DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM						/* Custom */
	};

	/* Dynamik Vertex Attribute */
	struct DMK_API DMKVertexAttribute : public DMKShaderInputAttribute {
		DMKVertexAttribute() = default;
		DMKVertexAttribute(DMKFormat format, UI32 dataCount, DMKVertexAttributeType attributeType)
			: DMKShaderInputAttribute(format, dataCount), attributeType(attributeType) {}
		~DMKVertexAttribute() = default;

		DMKVertexAttributeType attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	};

	/* This contains all the vertex attributes */
	class DMK_API DMKVertexLayout {
	public:
		DMKVertexLayout() {}
		~DMKVertexLayout() {}

		/* Get the size of the vertex using the attributes */
		const UI64 getVertexSize() const;

		/* Vertex attributes */
		ARRAY<DMKVertexAttribute> attributes;

		/*
		 Get the vertex layout as shader input attributes.
		*/
		ARRAY<DMKShaderInputAttribute> getInputAttributes() const;

	public:		/* Helper methods */
		/*
		 Create a basic vertex layout.
		 This contains,
		 - Position				[Vector3F * 1]
		 - Color				[Vector3F * 1]
		 - Texture Coordinates	[Vector2F * 1]
		*/
		static DMKVertexLayout createBasic();

		/*
		 Create a basic Image Based Lighting vertex layout.
		 This contains,
		 - Position				[Vector3F * 1]
		 - Normal				[Vector3F * 1]
		 - Color				[Vector2F * 1]
		*/
		static DMKVertexLayout createBasicIBL();

		/*
		 Create an animated vertex layout.
		 This contains,
		 - Position				[Vector3F * 1]
		 - Normal				[Vector3F * 1]
		 - UV					[Vector2F * 1]
		 - Color				[Vector3F * 1]
		 - boneWeights			[Float * 4]
		 - boneIDs				[unsigned int * 4]
		*/
		static DMKVertexLayout createAnimated();

		/*
		 Create a bounding box vertex layout.
		 This contains,
		 - Position				[Vector3F * 1]
		 - Color				[Vector4F * 1]
		*/
		static DMKVertexLayout createBoundingBox();

		/*
		 Create a basic skybox vertex layout.
		 This contains,
		 -  Position			[Vector3F * 1]
		*/
		static DMKVertexLayout createBasicSkybox();

	public:		/* Operators */
		B1 operator==(const DMKVertexLayout& other) const;
	};

	/*
	 Dynamik Vertex Buffer
	 This object is capable of storing all the vertexes of a given mesh.

	 The best way to load data to the vertex buffer is to first allocate the buffer with the required size,
	 and then move data at once or sequentially.
	*/
	class DMK_API DMKVertexBuffer {
	public:
		DMKVertexBuffer()
			: layout({}), _allocationSize(0), pDataStore(nullptr) {}
		DMKVertexBuffer(const DMKVertexLayout& layout)
			: layout(layout), _allocationSize(0), pDataStore(nullptr) {}
		~DMKVertexBuffer() {}

		/*
		 Initialize the buffer.

		 @param dataCount: The total number of vertexes the buffer will have.
		*/
		void initialize(UI64 dataCount);

		/*
		 Initialize the buffer.

		 @param dataCount: The total number of vertexes the buffer will have.
		 @param layout: The vertex layout.
		*/
		void initialize(UI64 dataCount, DMKVertexLayout layout);

		/*
		 Set the vertex layout.

		 @param layout: The vertex layout.
		*/
		void setLayout(const DMKVertexLayout& layout);

		/*
		 Get the vertex layout.
		*/
		DMKVertexLayout getLayout() const;

		/*
		 Get the data count (size).
		*/
		UI64 size() const;

		/*
		 Get the size of a single vertex (stride).
		*/
		UI64 stride() const;

		/*
		 Get the total byte size of the buffer.
		*/
		UI64 byteSize() const;

		/*
		 Clear the buffer.
		*/
		void clear();

		/*
		 Get the data pointer.
		*/
		VPTR data() const;

		/*
		 Add data to the buffer.

		 @param source: Source pointer from which to load the data.
		 @param byteCount: Byte size to copy from the source address.
		 @param offset: The offset of the buffer to which the data are added.
		*/
		void addData(const VPTR source, const UI64& byteCount, const UI64& offset);

		/*
		 Set data to the whole size of the buffer.

		 @param source: The source address of the data.
		*/
		void setData(const VPTR source);

		/*
		 Set null to a block of data in the buffer. This is used if the layout requested data are not
		 available in the input file (asset file).

		 @param byteSize: The number of bytes to be zeroed.
		 @param offset: The offset to which the zero values are set in the buffer.
		*/
		void setNull(const UI64& byteSize, const UI64& offset);

		/*
		 Update a single vertex in the vertex buffer.

		 @param index: Index of the vertex.
		 @param data: Data to be added.
		*/
		void updateVertex(const UI64& index, const VPTR data);

		/*
		 Update a single vertex attribute.

		 @param index: Index of the vertex to update.
		 @param data: Data to be added.
		 @param attribute: The attribute to be updated.
		*/
		void updateVertexAttribute(const UI64& index, const VPTR data, const DMKVertexAttributeType& attribute);

	public:		/* Buffer Data */
		/* Vertex Layout */
		DMKVertexLayout layout = {};

		/* Data Store */
		VPTR pDataStore = nullptr;

	private:
		/*
		 Find the vertex attribute offset.
		*/
		UI64 _findAttributeOffset(DMKVertexAttributeType attributeType);

		/*
		 Get the attribute size.
		*/
		UI64 _getAttributeSize(DMKVertexAttributeType attributeType);

		/* Total allocation size of the buffer */
		UI64 _allocationSize = 0;
	};
}

#endif // !_DYNAMIK_VERTEX_BUFFER_H
