// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_UNIFORM_H
#define _DYNAMIK_UNIFORM_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

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

	/*
	 Dynamik Uniform Buffer Object
	 Uniform data are passed to the Dynamik Engine using this object.
	 Uniform buffers are controlled by the users. This means that the creation, submission, updating and
	 termination (not explicitly required) are done by the users.
	 */
	class DMK_API DMKUniformBufferObject {
		/* Uniform buffer attribute */
		struct DMK_API Attribute {
			UI64 byteSize = 0;
			UI64 offset = 0;
		};

		/* Uniform buffer attribute data */
		struct DMK_API UniformBufferAttribute {
			STRING name = TEXT("");
			UI64 byteSize = 0;
			UI64 offset = 0;
		};

	public:
		DMKUniformBufferObject(UI32 binding = 0) : bindingLocation(binding) {}
		~DMKUniformBufferObject() = default;

		/*
		 Add an attribute to the uniform buffer object.
		 Every attribute in the buffer object has a unique name. This name doesn't need to be the same as in 
		 the shader, but the name is used to identify an attribute in the buffer.
		 Offsets to all the attributes are calculated internally. This means that all the attributes are to
		 be provided sequentially in the ascending order (in the list they should be).

		 @param name: The name of the attribute.
		 @param attribSize: The byte size of the attribute.
		*/
		void addAttribute(const STRING& name, const UI64& attribSize);

		/*
		 Get the stored attributes.
		*/
		ARRAY<UniformBufferAttribute> getAttributes() const;

		/*
		 Initialize the buffer.
		 This allocates the buffer and initializes the whole buffer to zero. This function needs to be called
		 externally. Meaning that the user must call this after adding all the attributes.
		*/
		void initialize();

		/*
		 Set data to an attribute.
		 This attribute is identifies by the name and an additional offset can be added is the attribute 
		 contains an array.

		 @param name: The name of the attribute.
		 @param data: The data to be added to the attribute.
		 @param offset: The offset to be added to the attribute.
		*/
		void setData(const STRING& name, VPTR data, const UI64& offset = 0);

		/*
		 Set data to the whole buffer object.

		 @param data: The data to set to the buffer.
		*/
		void setData(VPTR data);

		/*
		 Get the data pointer to the attribute. 
		 An offset will be added to the attribute data pointer.

		 @param name: The name of the attribute.
		 @param offset: The offset to be added to the pointer.
		*/
		VPTR getData(const STRING& name, const UI64& offset = 0);

		/*
		 Sets 0 to the whole store.
		*/
		void setZero();

		/* Clear all the stored values in the buffer */
		void clear();

		/*
		 Get the uniform data.
		*/
		VPTR data() const;

		/*
		 Get the byte size of the object.
		*/
		UI64 byteSize() const;

		/*
		 Set the uniform binding location.

		 @param binding: The shader binding location.
		*/
		void setBindingLocation(const UI32& binding);

		/*
		 Get the shader binding location of the uniform.
		*/
		UI64 getBindingLocation() const;

		/*
		 Set the uniform type of the buffer.

		 @param uniformType: The type of the uniform.
		*/
		void setUniformType(const DMKUniformType& uniformType);

		/*
		 Get the uniform buffer type.
		*/
		DMKUniformType getUniformType() const;

	private:	/* Private Data Store */
		std::unordered_map<STRING, Attribute> attributeMap;
		VPTR pUniformBufferStorage = nullptr;

	public:		/* Public Data */
		UI64 uByteSize = 0;
		UI32 bindingLocation = 0;
		DMKUniformType type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;
	};
}

#endif // !_DYNAMIK_UNIFORM_H
