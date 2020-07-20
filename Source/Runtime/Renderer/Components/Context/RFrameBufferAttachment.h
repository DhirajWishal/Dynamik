// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_FRAME_BUFFER_ATTACHMENT_H
#define _DYNAMIK_RENDERER_FRAME_BUFFER_ATTACHMENT_H

#include "../RCoreObject.h"
#include "../Primitives/RImage.h"

namespace Dynamik
{
	/* Frame Buffer Attachment Info */
	struct DMK_API RFrameBufferAttachmentInfo {
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
		DMKSampleCount msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
		UI32 imageWidth = 0;
		UI32 imageHeight = 0;
	};

	/*
	 Renderer Frame Buffer Attachment
	*/
	class DMK_API RFrameBufferAttachment {
	public:
		RFrameBufferAttachment() {}
		virtual ~RFrameBufferAttachment() {}

		virtual void initialize(RCoreObject* pCoreObject, RFrameBufferAttachmentInfo info) {}
		virtual void terminate(RCoreObject* pCoreObject) {}

		DMK_FORCEINLINE void setImage(RImage* pImage) { pImageAttachment = pImage; }

		RImage* pImageAttachment = nullptr;
	};
}

#endif // !_DYNAMIK_RENDERER_FRAME_BUFFER_ATTACHMENT_H
