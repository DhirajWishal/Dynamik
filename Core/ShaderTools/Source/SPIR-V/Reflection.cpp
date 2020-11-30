// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ShaderTools/SPIR-V/Reflection.h"
#include "Core/ErrorHandler/Logger.h"
#include "ShaderTools/SPIR-V/Utilities.h"

#include <spirv_glsl.hpp>

namespace DMK
{
	namespace ShaderTools
	{
		ReflectionDigest SPIRVReflection::Reflect(const GraphicsCore::ShaderCode& mShaderCode)
		{
			// Create the reflection digest object.
			ReflectionDigest mDigest = {};

			// Check if the shader code type is correct.
			if (mShaderCode.GetCodeType() != GraphicsCore::ShaderCodeType::SPIR_V)
			{
				Logger::LogError(TEXT("Invalid shader code type sent to the SPIR-V Reflection! Make sure that the code type is SPIR-V."));
				return mDigest;
			}

			// Setup the compiler and data structures.
			spirv_cross::Compiler mCompiler(std::move(Utilities::ResolvePadding(mShaderCode.mShaderCode)));
			spirv_cross::ShaderResources mResources = mCompiler.get_shader_resources();
			spirv_cross::SPIRType mType = {};

			// Calculate the shader offset.
			UI64 mShaderOffset = 0;

			// Resolve uniform buffers.
			for (auto& resource : mResources.uniform_buffers)
			{
				// Create the uniform buffer object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::UNIFORM_BUFFER, mCompiler.get_decoration(resource.id, spv::DecorationBinding));

				// Resolve the uniform attributes.
				for (UI32 index = 0; index < mCompiler.get_type(resource.base_type_id).member_types.size(); index++)
				{
					auto& Ty = mCompiler.get_type(mCompiler.get_type(resource.base_type_id).member_types[index]);
					UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
					mShaderOffset += byteSize;

					mUniform.AddAttribute(mCompiler.get_member_name(resource.base_type_id, index).c_str(), static_cast<DataType>(byteSize));
				}

				// Initialize the uniform and add it to the digest.
				mUniform.Initialize();
				mDigest.mUniforms.push_back(std::move(mUniform));
			}

			// Resolve storage buffers.
			for (auto& resource : mResources.storage_buffers)
			{
				// Create the storage buffer object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::STORAGE_BUFFER, mCompiler.get_decoration(resource.id, spv::DecorationBinding));
			
				// Resolve the uniform attributes.
				for (UI32 index = 0; index < mCompiler.get_type(resource.base_type_id).member_types.size(); index++)
				{
					auto& Ty = mCompiler.get_type(mCompiler.get_type(resource.base_type_id).member_types[index]);
					UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
					mShaderOffset += byteSize;

					mUniform.AddAttribute(mCompiler.get_member_name(resource.base_type_id, index).c_str(), static_cast<DataType>(byteSize));
				}

				// Initialize the uniform and add it to the digest.
				mUniform.Initialize();
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			// Resolve shader inputs.
			for (auto& resource : mResources.stage_inputs)
			{
				// Create the input attribute.
				GraphicsCore::ShaderAttribute mInputAttribute = {};
				mInputAttribute.mLocation = mCompiler.get_decoration(resource.id, spv::DecorationLocation);
				mInputAttribute.mName = std::move(mCompiler.get_name(resource.id));

				auto& Ty = mCompiler.get_type(resource.base_type_id);
				mInputAttribute.mLayerCount = Ty.columns;
				mInputAttribute.mDataType = static_cast<DataType>((Ty.width / 8) * (Ty.vecsize == 3 ? 4 : Ty.vecsize));

				mDigest.mInputAttributes.insert(mDigest.mInputAttributes.end(), std::move(mInputAttribute));
			}


			// Resolve shader outputs.
			for (auto& resource : mResources.stage_outputs)
			{
				// Create the output attribute.
				GraphicsCore::ShaderAttribute mOutputAttribute = {};
				mOutputAttribute.mLocation = mCompiler.get_decoration(resource.id, spv::DecorationLocation);
				mOutputAttribute.mName = std::move(mCompiler.get_name(resource.id));

				auto& Ty = mCompiler.get_type(resource.base_type_id);
				mOutputAttribute.mLayerCount = Ty.columns;
				mOutputAttribute.mDataType = static_cast<DataType>((Ty.width / 8) * (Ty.vecsize == 3 ? 4 : Ty.vecsize));

				mDigest.mOutputAttributes.insert(mDigest.mOutputAttributes.end(), std::move(mOutputAttribute));
			}

			// Resolve storage images.
			for (auto& resource : mResources.storage_images)
			{
				// Create the storage image uniform object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::STORAGE_IMAGE, mCompiler.get_decoration(resource.id, spv::DecorationBinding));
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			// Resolve image sampler.
			for (auto& resource : mResources.sampled_images)
			{
				// Create the image sampler uniform object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::SAMPLER_2D, mCompiler.get_decoration(resource.id, spv::DecorationBinding));
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			// Resolve seperate images.
			for (auto& resource : mResources.separate_images)
			{
				// Create the seperate image uniform object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::SAMPLER_2D, mCompiler.get_decoration(resource.id, spv::DecorationBinding));
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			// Resolve seperate sampler.
			for (auto& resource : mResources.separate_samplers)
			{
				// Create the seperate sampler uniform object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::SAMPLER_2D, mCompiler.get_decoration(resource.id, spv::DecorationBinding));
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			// Resolve accelleration structure.
			for (auto& resource : mResources.acceleration_structures)
			{
				// Create the acceleration structure uniform.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::ACCELERATION_STRUCTURE, mCompiler.get_decoration(resource.id, spv::DecorationBinding));
				
				// Resolve the structure attributes.
				for (UI32 index = 0; index < mCompiler.get_type(resource.base_type_id).member_types.size(); index++)
				{
					auto& Ty = mCompiler.get_type(mCompiler.get_type(resource.base_type_id).member_types[index]);
					UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
					mShaderOffset += byteSize;

					mUniform.AddAttribute(mCompiler.get_member_name(resource.base_type_id, index).c_str(), static_cast<DataType>(byteSize));
				}

				// Initialize the uniform and add it to the digest.
				mUniform.Initialize();
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			// Resolve constant buffers.
			for (auto& resource : mResources.push_constant_buffers)
			{
				// Create the push constant object.
				GraphicsCore::Uniform mUniform(GraphicsCore::UniformType::CONSTANT, mCompiler.get_decoration(resource.id, spv::DecorationBinding));

				// Resolve the buffer attributes.
				for (UI32 index = 0; index < mCompiler.get_type(resource.base_type_id).member_types.size(); index++)
				{
					auto& Ty = mCompiler.get_type(mCompiler.get_type(resource.base_type_id).member_types[index]);
					UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
					mShaderOffset += byteSize;

					mUniform.AddAttribute(mCompiler.get_member_name(resource.base_type_id, index).c_str(), static_cast<DataType>(byteSize));
				}

				// Initialize the uniform and add it to the digest.
				mUniform.Initialize();
				mDigest.mUniforms.insert(mDigest.mUniforms.end(), std::move(mUniform));
			}

			return mDigest;
		}
	}
}