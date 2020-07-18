// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_ATTACHMENT_H
#define _DYNAMIK_COMPONENT_ATTACHMENT_H

#include "Core/Math/Matrix/Matrix4F.h"
#include "Core/Objects/Resources/Uniform.h"

namespace Dynamik
{
	enum class DMK_API DMKComponentAttachmentType {
		DMK_COMPONENT_ATTACHMENT_TYPE_BOUNDING_BOX,
	};

	/*
	 Dynamik Component Attachment
	*/
	class DMK_API DMKComponentAttachment {
	public:
		DMKComponentAttachment() {}
		DMKComponentAttachment(DMKComponentAttachmentType type) : attachmentType(type) {}
		virtual ~DMKComponentAttachment() {}

		virtual void initialize() {}
		virtual void initialize(Matrix4F parentTransform) {}
		virtual void update() {}
		virtual DMKUniformBufferObject getUniform() { return uniformBufferObject; }

		DMKComponentAttachmentType attachmentType = DMKComponentAttachmentType::DMK_COMPONENT_ATTACHMENT_TYPE_BOUNDING_BOX;
		DMKUniformBufferObject uniformBufferObject;
	};
}

#endif // !_DYNAMIK_COMPONENT_ATTACHMENT_H
