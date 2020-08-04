// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_ATTACHMENT_H
#define _DYNAMIK_COMPONENT_ATTACHMENT_H

#include "Core/Math/Matrix/Matrix4F.h"
#include "Core/Objects/Resources/UniformBuffer.h"

#include "../Component.h"

namespace Dynamik
{
	enum class DMK_API DMKComponentAttachmentType {
		DMK_COMPONENT_ATTACHMENT_TYPE_BOUNDING_BOX,
	};

	/*
	 Dynamik Component Attachment

	 Component attachments contain a pointer to the component which it is attached to. These components are
	 attached to entities the same way as attaching components.
	*/
	class DMK_API DMKComponentAttachment {
	public:
		DMKComponentAttachment() {}
		DMKComponentAttachment(DMKComponent* pComponent, DMKComponentAttachmentType type) :
			pParentComponent(pComponent), attachmentType(type) {}
		virtual ~DMKComponentAttachment() {}

		virtual void initialize() {}
		virtual void initialize(Matrix4F parentTransform) {}
		virtual void update() {}
		virtual DMKUniformBuffer& getUniform() { return uniformBufferObject; }

		/*
		 Set the parent renderable component.

		 @param pComponent: The renderable component pointer.
		*/
		void setParentComponent(DMKComponent* pComponent) { pParentComponent = pComponent; }

		/*
		 Get the parent component.
		*/
		DMKComponent* getParentComponent() const { return pParentComponent; }

		DMKUniformBuffer uniformBufferObject;
		DMKComponent* pParentComponent = nullptr;
		DMKComponentAttachmentType attachmentType = DMKComponentAttachmentType::DMK_COMPONENT_ATTACHMENT_TYPE_BOUNDING_BOX;
	};
}

#endif // !_DYNAMIK_COMPONENT_ATTACHMENT_H
