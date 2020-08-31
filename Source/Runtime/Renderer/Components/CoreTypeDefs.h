// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDER_CORE_TYPE_DEFINES_H
#define _DYNAMIK_RENDER_CORE_TYPE_DEFINES_H

/*
 This file contains all the necessary type defines to create a rendering core. Since the engine supports Vulkan
 by default, these types are directly Vulkan compatible.
*/
#include "Core/Macros/Global.h"

/*
 Dynamik Render Pipeline
 This defines how the renderer renders a given scene.
*/
enum class DMK_API DMKRenderPipeline {
	DMK_RENDER_PIPELINE_DEBUG,
	DMK_RENDER_PIPELINE_PBR,
};

/* Subpass Attachment Load Op */
enum class DMK_API RSubpassAttachmentLoadOp {
	SUBPASS_ATTACHMENT_LOAD_OP_LOAD,
	SUBPASS_ATTACHMENT_LOAD_OP_CLEAR,
	SUBPASS_ATTACHMENT_LOAD_OP_DONT_CARE,
};

/* Subpass Attachment Store Op */
enum class DMK_API RSubpassAttachmentStoreOp {
	SUBPASS_ATTACHMENT_STORE_OP_STORE = 0,
	SUBPASS_ATTACHMENT_STORE_OP_DONT_CARE = 1,
	SUBPASS_ATTACHMENT_STORE_OP_NONE_QCOM = 1000301000,
};

#endif // !_DYNAMIK_RENDER_CORE_TYPE_DEFINES_H
