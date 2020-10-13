// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDER_CONTEXT_TYPE_DEFINES_H
#define _DYNAMIK_RENDER_CONTEXT_TYPE_DEFINES_H

/*
 This file contains all the necessary type defined needed for creating render contexts. Since the engine supports
 Vulkan by default, these types are directly vulkan compatible.
*/
#include "Core/Macros/Global.h"

/*
 Render context types
*/
enum class DMKRenderContextType {
	DMK_RENDER_CONTEXT_DEFAULT,
	DMK_RENDER_CONTEXT_DEFAULT_VR,
	DMK_RENDER_CONTEXT_2D,
	DMK_RENDER_CONTEXT_3D,
	DMK_RENDER_CONTEXT_DEBUG,
	DMK_RENDER_CONTEXT_DEBUG_VR,
};

/* Render Pass Attachment enum */
enum class DMK_API RenderPassAttachment {
	RENDER_PASS_ATTACHMENTS_SWAPCHAIN,
	RENDER_PASS_ATTACHMENTS_DEPTH,
	RENDER_PASS_ATTACHMENTS_COLOR,
	RENDER_PASS_ATTACHMENTS_OVERLAY,
};

/* Renderer Sub Pass Content Type */
enum class DMK_API RSubpassContentType {
	SUBPASS_CONTENT_TYPE_INLINE,
	SUBPASS_CONTENT_TYPE_SECONDARY_COMMAND_BUFFER,
};

#endif // !_DYNAMIK_RENDER_CONTEXT_TYPE_DEFINES_H