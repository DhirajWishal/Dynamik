// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Uniform Type enum.
		 */
		enum class UniformType : UI8 {
			UNDEFINED,
			UNIFORM_BUFFER,
			STORAGE_BUFFER,
			UNIFORM_BUFFER_DYNAMIC,
			STORAGE_BUFFER_DYNAMIC,
			UNIFORM_TEXEL_BUFFER,
			STORAGE_TEXEL_BUFFER,
			INPUT_ATTACHMENT,
			STORAGE_IMAGE,
			CONSTANT,
			SAMPLER_2D,
			SAMPLER_CUBE,
			SAMPLER_2D_ARRAY,
			SAMPLER_CUBE_ARRAY,
			ACCELERATION_STRUCTURE,
		};

		/**
		 * Uniform object.
		 * This stores uniform information which is submitted to shaders using the graphics or compute pipelines.
		 * If the uniform is a sampler, the uniform will not take any data in as it will be passed directly to the
		 * shader.
		 */
		class Uniform {
			/**
			 * Uniform Attribute structure.
			 * This represents a single attribute in the uniform.
			 */
			struct UniformAttribute {
				UI64 mOffset = 0;	// Offset of the attribute in memory.
				UI64 mLayerCount = 0;	// Number of array layers present.
				DataType mDataType = DataType::UNDEFINED;	// The type of the attribute.

				/**
				 * Get the type size using the enum.
				 *
				 * @return The size in bytes.
				 */
				UI64 GetTypeSize() const { return static_cast<UI8>(mDataType); }

				/**
				 * Get the size of the attribute in bytes.
				 *
				 * @return The size of the uniform in bytes.
				 */
				UI64 Size() const { return GetTypeSize() * mLayerCount; }
			};

		public:
			/**
			 * Construct the uniform using the uniform type and binding.
			 *
			 * @param mType: The uniform type. Default is UniformType::UNIFORM_BUFFER.
			 * @param mBinding: The binding of the uniform. Default is 0.
			 */
			Uniform(UniformType mType = UniformType::UNIFORM_BUFFER, UI64 mBinding = 0)
				: mType(mType), mBinding(mBinding) {}

			/**
			 * Default destructor.
			 */
			~Uniform() {}

			/**
			 * Get the uniform type.
			 *
			 * @return UniformType enum.
			 */
			UniformType GetType() const { return mType; }

			/**
			 * Get the uniform binding.
			 *
			 * @return The binding.
			 */
			UI64 GetBinding() const { return mBinding; }

			/**
			 * Get the size of the uniform.
			 *
			 * @return The size in bytes.
			 */
			UI64 Size() const { return mSize; }

			/**
			 * Get the data pointer of the uniform.
			 *
			 * @return Const void pointer.
			 */
			const void* Data() const { return pDataStore; }

		public:
			/**
			 * Add an attribute to the uniform.
			 *
			 * @param pName: The attribute name.
			 * @param mDatType: The type attribute.
			 * @param layerCount: The number of layers the attribute has (the array size). Default is 1.
			 */
			void AddAttribute(const char* pName, DataType mDatType, UI64 layerCount = 1);

			/**
			 * Get an attribute location in the uniform.
			 *
			 * @param pName: The name of the attribute.
			 * @param layer: The layer number (index) of the attribute. Default is 0.
			 * @return Void pointer.
			 */
			void* GetAttributeLocation(const char* pName, UI64 layer = 0);

			/**
			 * Get an attribute from the uniform, casted to a type pointer.
			 *
			 * @tparam Type: The type to be casted to.
			 * @param pName: The name of the attribute.
			 * @param layer: The layer number (index) of the attribute. Default is 0.
			 * @return Type pointer.
			 */
			template<class Type>
			Type* GetCasted(const char* pName, UI64 layer = 0)
			{
				return static_cast<Type*>(GetAttributeLocation(pName, layer));
			}

		public:
			/**
			 * Initialize the uniform.
			 * Initialize the uniform.
			 * This method is only available if at least one attribute is present in the uniform. If the uniform is
			 * a sampler, this method can be skipped.
			 */
			void Initialize();

			/**
			 * Terminate the uniform.
			 */
			void Terminate();

		private:
			std::unordered_map<String, UniformAttribute> mAttributeMap;	// The attribute map.
			void* pDataStore = nullptr;	// Uniform data store.
			UI64 mSize = 0;	// The size of the uniform.
			UI64 mBinding = 0;	// Binding of the uniform in the shader.
			UniformType mType = UniformType::UNDEFINED;	// The uniform type.
		};
	}
}