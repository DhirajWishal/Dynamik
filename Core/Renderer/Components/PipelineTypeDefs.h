// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PIPELINE_TYPE_DEFINES_H
#define _DYNAMIK_PIPELINE_TYPE_DEFINES_H

#include "PrimitiveTypeDefs.h"
#include "Core/Math/Vector/Vector2F.h"
#include "Core/Types/StaticArray.h"

/* Renderer Primitive Topology */
enum class DMK_API RPrimitiveTopology {
	PRIMITIVE_TOPOLOGY_POINT_LIST,
	PRIMITIVE_TOPOLOGY_LINE_LIST,
	PRIMITIVE_TOPOLOGY_LINE_STRIP,
	PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
	PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
	PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
	PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
	PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
	PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
	PRIMITIVE_TOPOLOGY_PATCH_LIST,
};

/* Renderer Polygon Mode */
enum class DMK_API RPolygonMode {
	POLYGON_MODE_FILL,
	POLYGON_MODE_LINE,
	POLYGON_MODE_POINT,
	POLYGON_MODE_FILL_RECTANGLE,
};

/* Renderer Cull Mode */
enum class DMK_API RCullMode {
	CULL_MODE_NONE,
	CULL_MODE_FRONT_BIT,
	CULL_MODE_BACK_BIT,
	CULL_MODE_FRONT_AND_BACK_BIT,
};

/* Renderer Front Face */
enum class DMK_API RFrontFace {
	FRONT_FACE_COUNTER_CLOCKWISE,
	FRONT_FACE_CLOCKWISE,
};

/* Renderer Logic Op */
enum class DMK_API RLogicOp {
	LOGIC_OP_CLEAR,
	LOGIC_OP_AND,
	LOGIC_OP_AND_REVERSE,
	LOGIC_OP_COPY,
	LOGIC_OP_AND_INVERTED,
	LOGIC_OP_NO_OP,
	LOGIC_OP_XOR,
	LOGIC_OP_OR,
	LOGIC_OP_NOR,
	LOGIC_OP_EQUIVALENT,
	LOGIC_OP_INVERT,
	LOGIC_OP_OR_REVERSE,
	LOGIC_OP_COPY_INVERTED,
	LOGIC_OP_OR_INVERTED,
	LOGIC_OP_NAND,
	LOGIC_OP_SET,
};

/* Renderer Dynamic State */
enum class DMK_API RDynamicState {
	DYNAMIC_STATE_VIEWPORT,
	DYNAMIC_STATE_SCISSOR,
	DYNAMIC_STATE_LINE_WIDTH,
	DYNAMIC_STATE_DEPTH_BIAS,
	DYNAMIC_STATE_BLEND_CONSTANTS,
	DYNAMIC_STATE_DEPTH_BOUNDS,
	DYNAMIC_STATE_STENCIL_COMPARE_MASK,
	DYNAMIC_STATE_STENCIL_WRITE_MASK,
	DYNAMIC_STATE_STENCIL_REFERENCE,
	DYNAMIC_STATE_VIEWPORT_W_SCALING,
	DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
	DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
	DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE,
	DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER,
	DYNAMIC_STATE_EXCLUSIVE_SCISSOR,
	DYNAMIC_STATE_LINE_STIPPLE_EXT,
};

/* Renderer Color Blend Factor */
enum class DMK_API RColorBlendFactor {
	COLOR_BLEND_FACTOR_ZERO,
	COLOR_BLEND_FACTOR_ONE,
	COLOR_BLEND_FACTOR_SRC_COLOR,
	COLOR_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
	COLOR_BLEND_FACTOR_DST_COLOR,
	COLOR_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
	COLOR_BLEND_FACTOR_SRC_ALPHA,
	COLOR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
	COLOR_BLEND_FACTOR_DST_ALPHA,
	COLOR_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
	COLOR_BLEND_FACTOR_CONSTANT_COLOR,
	COLOR_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
	COLOR_BLEND_FACTOR_CONSTANT_ALPHA,
	COLOR_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
	COLOR_BLEND_FACTOR_SRC_ALPHA_SATURATE,
	COLOR_BLEND_FACTOR_SRC1_COLOR,
	COLOR_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
	COLOR_BLEND_FACTOR_SRC1_ALPHA,
	COLOR_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
};

/* Renderer Color Blend Op */
enum class DMK_API RColorBlendOp {
	COLOR_BLEND_OP_ADD,
	COLOR_BLEND_OP_SUBTRACT,
	COLOR_BLEND_OP_REVERSE_SUBTRACT,
	COLOR_BLEND_OP_MIN,
	COLOR_BLEND_OP_MAX,
	COLOR_BLEND_OP_ZERO,
	COLOR_BLEND_OP_SRC,
	COLOR_BLEND_OP_DST,
	COLOR_BLEND_OP_SRC_OVER,
	COLOR_BLEND_OP_DST_OVER,
	COLOR_BLEND_OP_SRC_IN,
	COLOR_BLEND_OP_DST_IN,
	COLOR_BLEND_OP_SRC_OUT,
	COLOR_BLEND_OP_DST_OUT,
	COLOR_BLEND_OP_SRC_ATOP,
	COLOR_BLEND_OP_DST_ATOP,
	COLOR_BLEND_OP_XOR,
	COLOR_BLEND_OP_MULTIPLY,
	COLOR_BLEND_OP_SCREEN,
	COLOR_BLEND_OP_OVERLAY,
	COLOR_BLEND_OP_DARKEN,
	COLOR_BLEND_OP_LIGHTEN,
	COLOR_BLEND_OP_COLORDODGE,
	COLOR_BLEND_OP_COLORBURN,
	COLOR_BLEND_OP_HARDLIGHT,
	COLOR_BLEND_OP_SOFTLIGHT,
	COLOR_BLEND_OP_DIFFERENCE,
	COLOR_BLEND_OP_EXCLUSION,
	COLOR_BLEND_OP_INVERT,
	COLOR_BLEND_OP_INVERT_RGB,
	COLOR_BLEND_OP_LINEARDODGE,
	COLOR_BLEND_OP_LINEARBURN,
	COLOR_BLEND_OP_VIVIDLIGHT,
	COLOR_BLEND_OP_LINEARLIGHT,
	COLOR_BLEND_OP_PINLIGHT,
	COLOR_BLEND_OP_HARDMIX,
	COLOR_BLEND_OP_HSL_HUE,
	COLOR_BLEND_OP_HSL_SATURATION,
	COLOR_BLEND_OP_HSL_COLOR,
	COLOR_BLEND_OP_HSL_LUMINOSITY,
	COLOR_BLEND_OP_PLUS,
	COLOR_BLEND_OP_PLUS_CLAMPED,
	COLOR_BLEND_OP_PLUS_CLAMPED_ALPHA,
	COLOR_BLEND_OP_PLUS_DARKER,
	COLOR_BLEND_OP_MINUS,
	COLOR_BLEND_OP_MINUS_CLAMPED,
	COLOR_BLEND_OP_CONTRAST,
	COLOR_BLEND_OP_INVERT_OVG,
	COLOR_BLEND_OP_RED,
	COLOR_BLEND_OP_GREEN,
	COLOR_BLEND_OP_BLUE,
};

/* Renderer Stencil Op */
enum class DMK_API RStencilOp {
	STENCIL_OP_KEEP,
	STENCIL_OP_ZERO,
	STENCIL_OP_REPLACE,
	STENCIL_OP_INCREMENT_AND_CLAMP,
	STENCIL_OP_DECREMENT_AND_CLAMP,
	STENCIL_OP_INVERT,
	STENCIL_OP_INCREMENT_AND_WRAP,
	STENCIL_OP_DECREMENT_AND_WRAP,
};

/* Renderer Color Blend State */
struct DMK_API RColorBlendState {
	RColorBlendFactor srcColorBlendFactor = {};
	RColorBlendFactor dstColorBlendFactor = {};
	RColorBlendOp colorBlendOp = {};
	RColorBlendFactor srcAlphaBlendFactor = {};
	RColorBlendFactor dstAlphaBlendFactor = {};
	RColorBlendOp alphaBlendOp = {};
	RColorComponent colorWriteMask = (RColorComponent)15;
	bool enable = false;
};

/* Renderer Depth Stencil Op State */
struct DMK_API RStencilOpState {
	RStencilOp failOp;
	RStencilOp passOp;
	RStencilOp depthFailOp;
	RStencilCompareOp compareOp;
	UI32 compareMask = 0;
	UI32 writeMask = 0;
	UI32 reference = 0;
};

/* Renderer Pipeline Primitive Assembly Info */
struct DMK_API RPipelinePrimitiveAssemblyInfo {
	RPrimitiveTopology primitiveTopology = RPrimitiveTopology::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	bool enablePrimitiveRestart = false;
};

/* Renderer Pipeline Tessellation State Control Info */
struct DMK_API RPipelineTessellationStateControlInfo {
	UI32 patchControlPoints = 0;
};

/* Renderer Pipeline Scissor Info */
struct DMK_API RPipelineScissorInfo {
	Vector2F offset = Vector2F(0.0f);
};

/* Renderer Pipeline Rasterizer info */
struct DMK_API RPipelineRasterizerInfo {
	RPolygonMode polygonMode = RPolygonMode::POLYGON_MODE_FILL;
	RCullMode cullMode = RCullMode::CULL_MODE_BACK_BIT;
	RFrontFace frontFace = RFrontFace::FRONT_FACE_COUNTER_CLOCKWISE;
	float lineWidth = 1.0f;
	float constantFactor = 0.0f;
	float slopeFactor = 0.0f;
	bool depthClampEnable = false;
	bool discardEnable = false;
	bool depthBiasEnable = false;
};

/* Renderer Pipeline Multi Sampling Info */
struct DMK_API RPipelineMultiSamplingInfo {
	DMKSampleCount sampleCount = DMK_SAMPLE_COUNT_32_BIT;
	float minSampleShading = 0.2f;
	bool enableSampleShading = false;
	bool enableAlphaToCoverage = false;
	bool enableAlphaToOne = false;
};

/* Renderer Pipeline Depth Stencil Info */
struct DMK_API RPipelineDepthStencilInfo {
	RStencilCompareOp compareOp = RStencilCompareOp::STENCIL_COMPARE_OP_LESS;
	RStencilOpState frontOpState;
	RStencilOpState backOpState;
	float minBounds = 0.0f;
	float maxBounds = 0.0f;
	bool enableStencil = true;
	bool enableWrite = true;
	bool enableBoundsTest = false;
	bool enableStencilTests = false;
};

/* Renderer Pipeline Color Blend Info */
struct DMK_API RPipelineColorBlendInfo {
	std::vector<RColorBlendState> blendStates;
	std::vector<RColorComponent> colorComponents;
	StaticArray<float, 4> blendConstants = {
		0.0f, 0.0f, 0.0f, 0.0f /* R, G, B, A */
	};
	RLogicOp blendLogicOp = RLogicOp::LOGIC_OP_CLEAR;
	bool enableColorBlendLogicOp = false;
};

#endif // !_DYNAMIK_PIPELINE_TYPE_DEFINES_H