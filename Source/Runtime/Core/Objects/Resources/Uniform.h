// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_UNIFORM_H
#define _DYNAMIK_UNIFORM_H

#include "ShaderModule.h"

namespace Dynamik
{
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
		DMK_UNIFORM_BUFFER_USAGE_MODEL,
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

		/* Buffer object container */
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
		BYTE* nextPointer = (BYTE*)uniformBufferStorage;

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

#endif // !_DYNAMIK_UNIFORM_H
