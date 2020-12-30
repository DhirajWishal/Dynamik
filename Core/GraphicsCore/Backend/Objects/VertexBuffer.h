// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_VERTEX_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_VERTEX_BUFFER_H

#include "Buffer.h"
#include "Core/Types/Utilities.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Vertex Attributes structure containing information about a single vertex attribute.
		 *
		 * DMK uses the DMK::Format enum to define the data format of the attribute.
		 */
		struct VertexAttribute {
			/**
			 * Default constructor.
			 */
			VertexAttribute() = default;

			/**
			 * Construct the object using the type and format it stores.
			 *
			 * @param type: The type of the attribute.
			 * @param format: The format of the attribute.
			 */
			VertexAttribute(DataType type, Format format) : type(type), format(format) {}

			/**
			 * Set the data type of the attribute.
			 *
			 * @param type: The Data Type of the attribute.
			 */
			void SetType(DataType type) { this->type = type; }

			/**
			 * Get the data type of the attrubute.
			 *
			 * @return DMK::DataType enum.
			 */
			DataType GetType() const { return type; }

			/**
			 * Get the size of the attribute.
			 *
			 * @return Unsigned 32 bit integer.
			 */
			UI32 Size() const { return Cast<UI32>(type); }

			/**
			 * Set the format of the attribute.
			 *
			 * @param format: The format of the data.
			 */
			void SetFormat(Format format) { this->format = format; }

			/**
			 * Get the format of the attribute.
			 *
			 * @return DMK::Format enum.
			 */
			Format GetFormat() const { return format; }

			DataType type = DataType::DATA_TYPE_UNDEFINED;	// The data type of the attribute.
			Format format = Format::FORMAT_UNDEFINED;	// The data format of the attribute.
		};

		/**
		 * Vertex structure for Dynamik.
		 * This structure contains information about a single vertex.
		 */
		struct Vertex {
			/**
			 * Default constructor.
			 */
			Vertex() = default;

			/**
			 * Construct the structure using attributes and binding.
			 *
			 * @param vAttributes: The vertex attributes.
			 * @param binding: The binding index of the vertex. Default is 0.
			 */
			Vertex(const std::vector<VertexAttribute>& vAttributes, UI32 binding = 0) : attributes(vAttributes), binding(binding) {}

			/**
			 * Add an attribute to the vertex.
			 *
			 * @param vAttribute: The attribute to be added.
			 */
			void AddAttribute(const VertexAttribute& vAttribute) { attributes.push_back(vAttribute); }

			/**
			 * Set the attributes of the vertex.
			 *
			 * @param vAttributes: Attribtues to be set.
			 */
			void SetAttributes(const std::vector<VertexAttribute>& vAttributes) { attributes = vAttributes; }

			/**
			 * Get an attribute from the vertex.
			 *
			 * @param index: The index of the attribute.
			 * @return const Vertex Attrubute structure.
			 */
			const VertexAttribute GetAttribute(UI64 index) const { return attributes[index]; }

			/**
			 * Get an attribute from the vertex.
			 *
			 * @param index: The index of the attribute.
			 * @return Vertex Attrubute structure.
			 */
			VertexAttribute GetAttribute(UI64 index) { return attributes[index]; }

			/**
			 * Get the pointer of the attributes.
			 *
			 * @return Pointer to the attrubutes.
			 */
			std::vector<VertexAttribute>* GetAttributes() const { return const_cast<std::vector<VertexAttribute>*>(&attributes); }

			/**
			 * Set the binding index of the vertex.
			 *
			 * @param binding: The binding index.
			 */
			void SetBinding(UI32 binding) { this->binding = binding; }

			/**
			 * Get the binding index of the vertex.
			 *
			 * @return Unsigned 32 bit integer.
			 */
			UI32 GetBinding() const { return binding; }

			/**
			 * Get the size of the vertex in bytes.
			 *
			 * @return Unsigned 64 bit integer.
			 */
			UI64 Size() const
			{
				UI64 size = 0;

				// Iterate through the attributes to calculate the size.
				for (auto itr = attributes.begin(); itr != attributes.end(); itr++)
					size += Cast<UI32>(itr->type);

				return size;
			}

			std::vector<VertexAttribute> attributes;	// Vertex attributes.
			UI32 binding = 0;	// Binding location of the vertex in the shader.
		};

		/**
		 * Vertex Buffer base class for Dynamik.
		 * This object is used to store vertex information.
		 */
		class VertexBuffer : public Buffer {
		public:
			/**
			 * Default constructor.
			 */
			VertexBuffer() {}

			/**
			 * Default destructor.
			 */
			virtual ~VertexBuffer() {}

			/**
			 * Set the vertex of the buffer.
			 *
			 * @param vertex: The vertex structure.
			 */
			void SetVertex(const Vertex& vertex) { this->vertex = vertex; }

			/**
			 * Get the pointer to the vertex.
			 *
			 * @return Pointer to the vertex data.
			 */
			Vertex* GetVertex() const { return const_cast<Vertex*>(&vertex); }

			/**
			 * Get the number of vertexes stored in the buffer.
			 *
			 * @return Unsigned 64 bit integer.
			 */
			UI64 GetVertexCount() const { return GetSize() / vertex.Size(); }

		protected:
			Vertex vertex = {};	// Vertex stored in the buffer.
		};

		/**
		 * Vertex Buffer Reference for Dynamik.
		 * Since the engine stores vertex buffers in multiple large vertex buffers, sorted by the size of the
		 * vertex. Because of this, almost all the vertexes are stored in one large vertex buffer.
		 * Because of this, we maintain an object named the Vertex Buffer Reference to store the following information,
		 * - Parent vertex buffer: The actual vertex buffer that contains the data.
		 * - Vertex offset: The number of vertexes to go from the begining to find the first vertex entry.
		 * - Vertex count: The number of vertexes associated with the vertex buffer.
		 */
		class VertexBufferRef {
		public:
			/**
			 * Default constructor.
			 */
			VertexBufferRef() {}

			/**
			 * Default destructor.
			 */
			~VertexBufferRef() {}

			VertexBuffer* pParentBuffer = nullptr;	// The parent vertex buffer.
			UI64 vertexOffset = 0;	// The vertex offset.
			UI64 vertexCount = 0;	// The vertex count.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_VERTEX_BUFFER_H
