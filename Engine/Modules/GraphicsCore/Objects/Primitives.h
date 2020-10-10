// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_PRIMITIVES_H
#define _DYNAMIK_GRAPHICS_CORE_PRIMITIVES_H

#include "Core/Types/DataTypes.h"
#include "Core/Types/Utilities.h"

namespace DMK
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Primitive Buffer
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Primitve Buffer for the Dynamik Engine.
	 * This object is used to store multiple elements of the same type.
	 */
	class DMK_API PrimitveBuffer {
	public:
		/**
		 * Default constructor.
		 *
		 * @param pData: The data pointer. Default is nullptr.
		 * @param byteSize: The size of the buffer in bytes. Default is 0.
		 * @param stride: The stride of the buffer in bytes. Default is 0.
		 */
		PrimitveBuffer(void* pData = nullptr, UI64 byteSize = 0, UI64 stride = 0)
			: pData(pData), byteSize(byteSize), stride(stride) {}

		/**
		 * Default destructor.
		 */
		virtual ~PrimitveBuffer() {}

		/**
		 * Set the data pointer of the buffer.
		 *
		 * @param pData: The pointer to the data.
		 */
		void SetDataPointer(void* pData) { this->pData = pData; }

		/**
		 * Get the data pointer.
		 */
		void* GetDataPointer() const { return pData; }

		/**
		 * Set the byte size of the buffer.
		 *
		 * @param size: The size of the buffer in bytes.
		 */
		void SetSize(UI64 size) { this->byteSize = size; }

		/**
		 * Get the byte size of the buffer.
		 */
		UI64 GetSize() const { return byteSize; }

		/**
		 * Set the stride of the buffer.
		 *
		 * @param stride: The stride of the buffer.
		 */
		void SetStride(UI64 stride) { this->stride = stride; }

		/**
		 * Get the stride of the buffer.
		 */
		UI64 GetStride() const { return stride; }

		/* Data */
	protected:
		void* pData = nullptr;
		UI64 byteSize = 0;
		UI64 stride = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Uniform Buffer
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Uniform Types for the Dynamik Engine.
	 */
	enum class DMK_API UniformType {
		UNIFORM_TYPE_UNIFORM_BUFFER,
		UNIFORM_TYPE_STORAGE_BUFFER,
		UNIFORM_TYPE_UNIFORM_BUFFER_DYNAMIC,
		UNIFORM_TYPE_STORAGE_BUFFER_DYNAMIC,
		UNIFORM_TYPE_UNIFORM_TEXEL_BUFFER,
		UNIFORM_TYPE_STORAGE_TEXEL_BUFFER,
		UNIFORM_TYPE_INPUT_ATTACHMENT,
		UNIFORM_TYPE_STORAGE_IMAGE,
		UNIFORM_TYPE_CONSTANT,
		UNIFORM_TYPE_SAMPLER_2D,
		UNIFORM_TYPE_SAMPLER_CUBE,
		UNIFORM_TYPE_SAMPLER_2D_ARRAY,
		UNIFORM_TYPE_SAMPLER_CUBE_ARRAY,
		UNIFORM_TYPE_ACCELERATION_STRUCTURE,
	};

	/**
	 * Uniform Buffer for the Dyamik Engine.
	 * This object is used to store information about data in the uniform buffer which can be pushed to shaders
	 * when rendering.
	 */
	class DMK_API UniformBuffer {
	public:
		/**
		 * Uniform Attribute structure.
		 * This object stores information about a single attribute in the uniform buffer.
		 */
		struct DMK_API UniformAttribute {
			UI64 byteSize = 0;	// Byte size of the attribute.
			UI64 offset = 0;	// Offset of the attribute in memory.
		};

	public:
		/**
		 * Default Contructor.
		 *
		 * @param binding: The binding of the uniform buffer in the shader. Default is 0.
		 * @param type: The type of the uniform buffer. Default is DMK_UNIFORM_TYPE_UNIFORM_BUFFER.
		 */
		UniformBuffer(UI64 binding = 0, UniformType type = UniformType::UNIFORM_TYPE_UNIFORM_BUFFER)
			: binding(binding), type(type) {}

		/**
		 * Default destructor.
		 */
		~UniformBuffer() {}

		/**
		 * Add an attribute to the uniform buffer.
		 * This automatically calculates the offset of the attributes.
		 */
		void AddAttribute(const STRING& name, UI64 size);

		/**
		 * Get an attribute from the uniform buffer.
		 * The user is allowed to cast it to the data type it points to.
		 *
		 * @param name: The name of the attribute.
		 * @tparam Type: The type to be casted to. Default is void.
		 */
		template<class Type = void>
		DMK_FORCEINLINE Type* GetAttribute(const STRING& name)
		{
			// Check if the attribute is added.
			if (attributeMap.find(name) != attributeMap.end())
				return reinterpret_cast<Type*>(IncrementPointer(pDataStore, attributeMap[name].offset));

			// Return nullptr if the attribute is not available.
			return nullptr;
		}

		/**
		 * Initialize the unform buffer.
		 */
		void Initialize();

		/**
		 * Terminate the uniform buffer.
		 */
		void Terminate();

		/**
		 * Get the data pointer of the uniform buffer.
		 */
		void* Data() const { return pDataStore; }

		/**
		 * Get the size of the buffer in bytes.
		 */
		UI64 Size() const { return size; }

		/**
		 * Get the binding of the buffer in the shader.
		 */
		UI64 Binding() const { return binding; }

		/**
		 * Get the uniform type of the buffer.
		 */
		UniformType GetUniformType() const { return type; }

		/**
		 * Get all the stored attributes in the uniform.
		 */
		std::vector<UniformAttribute> GetAttributes() const;

		/* Data */
	private:
		std::unordered_map<STRING, UniformAttribute> attributeMap;
		UI64 binding = 0;
		UI64 size = 0;
		void* pDataStore = nullptr;

		UniformType type = UniformType::UNIFORM_TYPE_UNIFORM_BUFFER;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_PRIMITIVES_H
