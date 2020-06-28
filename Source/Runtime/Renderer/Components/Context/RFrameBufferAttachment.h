// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_FRAME_BUFFER_ATTACHMENT_H
#define _DYNAMIK_RENDERER_FRAME_BUFFER_ATTACHMENT_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "RCoreObject.h"

namespace Dynamik
{
	/*
	 Renderer Frame Buffer Attachment
	*/
	class DMK_API RFrameBufferAttachment {
	public:
		RFrameBufferAttachment() {}
		virtual ~RFrameBufferAttachment() {}
	};
}

#endif // !_DYNAMIK_RENDERER_FRAME_BUFFER_ATTACHMENT_H
