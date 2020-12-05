// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Vertex Attribute Type enum.
		 */
		enum class VertexAttributeType : UI8 {
			UNDEFINED,					// Undefined attribute.
			POSITION,					// Position coordinates.
			NORMAL,						// Normal vectors.
			COLOR_0,					// Color coordinates 0.
			COLOR_1,					// Color coordinates 1.
			COLOR_2,					// Color coordinates 2.
			COLOR_3,					// Color coordinates 3.
			TEXTURE_COORDINATES_0,		// Texture coordinates 0.
			TEXTURE_COORDINATES_1,		// Texture coordinates 1.
			TEXTURE_COORDINATES_2,		// Texture coordinates 2.
			TEXTURE_COORDINATES_3,		// Texture coordinates 3.
			TEXTURE_COORDINATES_4,		// Texture coordinates 4.
			TEXTURE_COORDINATES_5,		// Texture coordinates 5.
			TEXTURE_COORDINATES_6,		// Texture coordinates 6.
			TEXTURE_COORDINATES_7,		// Texture coordinates 7.
			UV_COORDINATES,				// UV coordinates.
			TANGENT,					// Tangents.
			BITANGENT,					// Bi tangents.
			INTEGRITY,					// Integrity value.
			BONE_ID,					// Bone IDs.
			BONE_WEIGHT,				// Bone Weights.
			CUSTOM						// Custom.
		};

		/**
		 * Vertex Attribute structure.
		 * This defines a single attribute present in a vertex.
		 */
		struct VertexAttribute {
			/**
			 * Construct the attribute using the type, data tyoe and the layer count.
			 *
			 * @param type: The type of the attribute. Default is UNDEFINED.
			 * @param dataType: The data type of the attribute. Default is UNDEFINED.
			 * @param layerCount: The number of array layers. Default is 1.
			 */
			VertexAttribute(VertexAttributeType type = VertexAttributeType::UNDEFINED, DataType dataType = DataType::UNDEFINED, UI64 layerCount = 1)
				: mType(type), mDataType(dataType), mLayers(layerCount) {}

			/**
			 * Get the size of the attribute.
			 *
			 * @return The size in bytes.
			 */
			UI64 Size() const { return static_cast<UI64>(mDataType) * mLayers; }

			UI64 mLayers = 1;	// Layer count.
			VertexAttributeType mType = VertexAttributeType::UNDEFINED;	// Attribute type.
			DataType mDataType = DataType::UNDEFINED;	// Data type.
		};

		/**
		 * Vertex Buffer Object.
		 * This object stores information which will be passed to the Vertex Buffers.
		 * Once the buffer is submitted to the Graphics Backend, this object will be destroyed and a handle will be
		 * returned.
		 */
		class VertexBufferObject {
		public:
			VertexBufferObject() {}
			~VertexBufferObject() {}

			/**
			 * Get the hash of the layout.
			 */
			UI64 LayoutHash() const;

			/**
			 * Get the data store pointer.
			 *
			 * @return The pointer.
			 */
			void* Data() const { return pDataStore; }

			/**
			 * Get the size of the layout.
			 *
			 * @return The size in bytes.
			 */
			UI64 LayoutSize() const;

			/**
			 * Get the size of the buffer.
			 *
			 * @return The size in bytes.
			 */
			UI64 Size() const { return mSize; }

			/**
			 * Add an attribute to the vertex buffer's layout.
			 */
			void AddAttribute(VertexAttributeType type, DataType dataType, UI64 layerCount = 1);

			/**
			 * Set the attributes present in the vertex buffer.
			 *
			 * @param attributes: The attributes to be set.
			 */
			void SetAttributes(const std::vector<VertexAttribute>& attributes);

			/**
			 * Set the attributes present in the vertex buffer.
			 *
			 * @param attributes: The attributes to be set.
			 */
			void SetAttributes(std::vector<VertexAttribute>&& attributes);

		public:
			/**
			 * Initialize the vertex buffer.
			 */
			void Initialize();

			/**
			 * Terminate the vertex buffer.
			 */
			void Terminate();

		public:
			std::vector<VertexAttribute> mAttributes;	// The vertex attributes.

			void* pDataStore = nullptr;	// The data store pointer.
			UI64 mSize = 0;	// The size of the buffer.
		};

		/**
		 * Vertex Buffer Handle object.
		 * This object stores information about a single vertex buffer object.
		 */
		class VertexBufferHandle {
		public:
			VertexBufferHandle(const VertexBufferHandle&) = delete;
			VertexBufferHandle(VertexBufferHandle&&) = delete;

			/**
			 * Constrct the handle using the handle and the size.
			 *
			 * @param handle: The handle to be set. Default is 0.
			 * @param size: The size of the handle to be set. Default is 0.
			 */
			VertexBufferHandle(UI64 handle = 0, UI64 size = 0) : mHandle(handle), mSize(size) {}

			~VertexBufferHandle() {}

			/**
			 * Get the stored handle data.
			 *
			 * @return Handle integer.
			 */
			UI64 GetHandle() const { return mHandle; }

			/**
			 * Get the size of the buffer pointed by the handle.
			 *
			 * @return The size in bytes.
			 */
			UI64 GetSize() const { return mSize; }

		private:
			UI64 mHandle = 0;	// The vertex buffer handle.
			UI64 mSize = 0;
		};

		/**
		 * Vertex Presents are pre defined vertex layouts which can be used to create Vertex Buffer Objects.
		 */
		namespace VertexPresets
		{

		}
	}
}