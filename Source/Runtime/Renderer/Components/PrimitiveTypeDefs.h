// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_PRIMITIVE_TYPE_DEFINES_H
#define _DYNAMIK_RENDERER_PRIMITIVE_TYPE_DEFINES_H

/*
 This file contains all the definitions and enums for different RBL APIs. Since the Dynamik Engine's default
 RBL API is Vulkan, all these defines are directly Vulkan Compatible.
*/
#include "Core/Macros/Global.h"

/* Image Usage (OR operator can be used) */
enum DMK_API RImageUsage {
	IMAGE_USAGE_TRANSFER_SRC = BIT_SHIFT(0),
	IMAGE_USAGE_TRANSFER_DST = BIT_SHIFT(1),
	IMAGE_USAGE_RENDER = BIT_SHIFT(2),
	IMAGE_USAGE_STORAGE = BIT_SHIFT(3),
	IMAGE_USAGE_COLOR_ATTACHMENT = BIT_SHIFT(4),
	IMAGE_USAGE_DEPTH_ATTACHMENT = BIT_SHIFT(5),
	IMAGE_USAGE_TRANSIENT_ATTACHMENT = BIT_SHIFT(6),
	IMAGE_USAGE_INPUT_ATTACHMENT = BIT_SHIFT(7),
};

/* Resource Memory Type */
enum DMK_API RResourceMemoryType {
	RESOURCE_MEMORY_TYPE_DEVICE_LOCAL = BIT_SHIFT(0),
	RESOURCE_MEMORY_TYPE_HOST_VISIBLE = BIT_SHIFT(1),
	RESOURCE_MEMORY_TYPE_HOST_COHERENT = BIT_SHIFT(2),
	RESOURCE_MEMORY_TYPE_HOST_CACHED = BIT_SHIFT(3),
	RESOURCE_MEMORY_TYPE_PROTECTED = BIT_SHIFT(5),
};

/* Memory Access Types */
enum DMK_API RMemoryAccessType {
	MEMORY_ACCESS_TYPE_INDIRECT_COMMAND_READ = BIT_SHIFT(0),
	MEMORY_ACCESS_TYPE_INDEX_READ = BIT_SHIFT(1),
	MEMORY_ACCESS_TYPE_VERTEX_ATTRIBUTE_READ = BIT_SHIFT(2),
	MEMORY_ACCESS_TYPE_UNIFORM_READ = BIT_SHIFT(3),
	MEMORY_ACCESS_TYPE_INPUT_ATTACHMENT_READ = BIT_SHIFT(4),
	MEMORY_ACCESS_TYPE_SHADER_READ = BIT_SHIFT(5),
	MEMORY_ACCESS_TYPE_SHADER_WRITE = BIT_SHIFT(6),
	MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_READ = BIT_SHIFT(7),
	MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_WRITE = BIT_SHIFT(8),
	MEMORY_ACCESS_TYPE_DEPTH_STENCIL_ATTACHMENT_READ = BIT_SHIFT(9),
	MEMORY_ACCESS_TYPE_DEPTH_STENCIL_ATTACHMENT_WRITE = BIT_SHIFT(10),
	MEMORY_ACCESS_TYPE_TRANSFER_READ = BIT_SHIFT(11),
	MEMORY_ACCESS_TYPE_TRANSFER_WRITE = BIT_SHIFT(12),
	MEMORY_ACCESS_TYPE_HOST_READ = BIT_SHIFT(13),
	MEMORY_ACCESS_TYPE_HOST_WRITE = BIT_SHIFT(14),
	MEMORY_ACCESS_TYPE_MEMORY_READ = BIT_SHIFT(15),
	MEMORY_ACCESS_TYPE_MEMORY_WRITE = BIT_SHIFT(16)
};

/* Image Sampler Filter */
enum class DMK_API RImageSamplerFilter {
	IMAGE_SAMPLER_FILTER_NEAR = 0,
	IMAGE_SAMPLER_FILTER_LINEAR = 1,
	IMAGE_SAMPLER_FILTER_CUBIC = 1000015000,
};

/* Image Sampler Address Mode */
enum class DMK_API RImageSamplerAddressMode {
	IMAGE_SAMPLER_ADDRESS_MODE_REPEAT,
	IMAGE_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
	IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
	IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
	IMAGE_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE,
};

/* Image Sampler Border Color */
enum class DMK_API RImageSamplerBorderColor {
	IMAGE_SAMPLER_BORDER_COLOR_F32_TRANSPARENT_BLACK,
	IMAGE_SAMPLER_BORDER_COLOR_I32_TRANSPARENT_BLACK,
	IMAGE_SAMPLER_BORDER_COLOR_F32_OPAQUE_BLACK,
	IMAGE_SAMPLER_BORDER_COLOR_I32_OPAQUE_BLACK,
	IMAGE_SAMPLER_BORDER_COLOR_F32_OPAQUE_WHITE,
	IMAGE_SAMPLER_BORDER_COLOR_I32_OPAQUE_WHITE,
};

/* Dynamik Pipeline Compare Op */
enum class DMK_API RStencilCompareOp {
	STENCIL_COMPARE_OP_NEVER,
	STENCIL_COMPARE_OP_LESS,
	STENCIL_COMPARE_OP_EQUAL,
	STENCIL_COMPARE_OP_LESS_OR_EQUAL,
	STENCIL_COMPARE_OP_GREATER,
	STENCIL_COMPARE_OP_NOT_EQUAL,
	STENCIL_COMPARE_OP_GREATER_OR_EQUAL,
	STENCIL_COMPARE_OP_ALWAYS,
};

/* Image Sampler Mipmap mode */
enum class DMK_API RResourceMipMapMode {
	RESOURCE_MIPMAP_MODE_NEAREST,
	RESOURCE_MIPMAP_MODE_LINEAR,
};

/* Image Swizzle Components */
enum class DMK_API RImageSwizzleComponent {
	IMAGE_SWIZZLE_IDENTITY,
	IMAGE_SWIZZLE_ZERO,
	IMAGE_SWIZZLE_ONE,
	IMAGE_SWIZZLE_R,
	IMAGE_SWIZZLE_G,
	IMAGE_SWIZZLE_B,
	IMAGE_SWIZZLE_A,
};

/* Image Layouts */
enum class DMK_API RImageLayout {
	IMAGE_LAYOUT_UNDEFINED,
	IMAGE_LAYOUT_GENERAL,
	IMAGE_LAYOUT_COLOR_ATTACHMENT,
	IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT,
	IMAGE_LAYOUT_DEPTH_STECIL_READ_ONLY,
	IMAGE_LAYOUT_SHADER_READ_ONLY,
	IMAGE_LAYOUT_TRANSFER_SRC,
	IMAGE_LAYOUT_TRANSFER_DST,
	IMAGE_LAYOUT_PREINITIALIZED,
	IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT,
	IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY,
	IMAGE_LAYOUT_DEPTH_ATTACHMENT,
	IMAGE_LAYOUT_DEPTH_READ_ONLY,
	IMAGE_LAYOUT_STENCIL_ATTACHMENT,
	IMAGE_LAYOUT_STENCIL_READ_ONLY,
	IMAGE_LAYOUT_PRESENT_SRC,
	IMAGE_LAYOUT_SHARED_PRESENT,
	IMAGE_LAYOUT_SHADING_RATE,
	IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP,
};

/* Buffer Types */
enum class DMK_API RBufferType {
	BUFFER_TYPE_STAGGING,
	BUFFER_TYPE_VERTEX,
	BUFFER_TYPE_INDEX,
	BUFFER_TYPE_UNIFORM,
	BUFFER_TYPE_INDIRECT,
	BUFFER_TYPE_RAY_TRACING,
};

/* Color Component */
enum DMK_API RColorComponent {
	COLOR_COMPONENT_R_BIT = BIT_SHIFT(0),
	COLOR_COMPONENT_G_BIT = BIT_SHIFT(1),
	COLOR_COMPONENT_B_BIT = BIT_SHIFT(2),
	COLOR_COMPONENT_A_BIT = BIT_SHIFT(3),
};

/* Pipeline Stage */
enum DMK_API RPipelineStage {
	PIPELINE_STAGE_TOP_OF_PIPE = BIT_SHIFT(0),
	PIPELINE_STAGE_DRAW_INDIRECT = BIT_SHIFT(1),
	PIPELINE_STAGE_VERTEX_INPUT = BIT_SHIFT(2),
	PIPELINE_STAGE_VERTEX_SHADER = BIT_SHIFT(3),
	PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER = BIT_SHIFT(4),
	PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER = BIT_SHIFT(5),
	PIPELINE_STAGE_GEOMETRY_SHADER = BIT_SHIFT(6),
	PIPELINE_STAGE_FRAGMENT_SHADER = BIT_SHIFT(7),
	PIPELINE_STAGE_EARLY_FRAGMENT_TESTS = BIT_SHIFT(8),
	PIPELINE_STAGE_LATE_FRAGMENT_TESTS = BIT_SHIFT(9),
	PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT = BIT_SHIFT(10),
	PIPELINE_STAGE_COMPUTE_SHADER = BIT_SHIFT(11),
	PIPELINE_STAGE_TRANSFER = BIT_SHIFT(12),
	PIPELINE_STAGE_BOTTOM_OF_PIPE = BIT_SHIFT(13),
	PIPELINE_STAGE_HOST = BIT_SHIFT(14),
	PIPELINE_STAGE_ALL_GRAPHICS = BIT_SHIFT(15),
	PIPELINE_STAGE_ALL_COMMANDS = BIT_SHIFT(16)
};

/* Pipeline Dependency */
enum DMK_API RPipelineDependency {
	DEPENDENCY_BY_REGION = BIT_SHIFT(0),
	DEPENDENCY_DEVICE_GROUP = BIT_SHIFT(2),
	DEPENDENCY_VIEW_LOCAL = BIT_SHIFT(1),
};

#endif // !_DYNAMIK_RENDERER_PRIMITIVE_TYPE_DEFINES_H
