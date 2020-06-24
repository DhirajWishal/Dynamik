// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_PIPELINE_OBJECT_H
#define _DYNAMIK_RENDERER_PIPELINE_OBJECT_H

/*
 Author:	Dhiraj Wishal
 Date:		17/06/2020
*/
#include "RCoreObject.h"
#include "PipelineTypeDefs.h"
#include "RRenderTarget.h"

#include "Core/Object/Resource/ShaderModule.h"

namespace Dynamik
{
	class DMK_API RCoreObject;

	/* Renderer Pipeline Usage */
	enum class DMK_API RPipelineUsage {
		PIPELINE_USAGE_GRAPHICS,
		PIPELINE_USAGE_COMPUTE,
	};

	/*
	 Renderer Pipeline Create Info
	*/
	struct DMK_API RPipelineCreateInfo {
		RRenderTarget* pRenderTarget;
		ARRAY<DMKShaderModule> shaders;
		// Descriptors

		/* Primitive Assembly */
		RPrimitiveTopology primitiveTopology = RPrimitiveTopology::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		B1 enablePrimitiveRestart = false;

		/* Scissor */
		UI32 scissorCount = 1;
		ARRAY<Vector2F> offsets = { {0.0f, 0.0f} };

		/* Rasterizer */
		B1 depthClampEnable = false;
		B1 discardEnable = false;
		RPolygonMode polygonMode = RPolygonMode::POLYGON_MODE_FILL;
		F32 lineWidth = 1.0f;
		RCullMode cullMode = RCullMode::CULL_MODE_BACK_BIT;
		RFrontFace frontFace = RFrontFace::FRONT_FACE_COUNTER_CLOCKWISE;
		B1 depthBiasEnable = false;

		/* Multisampling */
		DMKSampleCount sampleCount = DMK_SAMPLE_COUNT_32_BIT;
		B1 enableSampleShading = false;
		F32 minSampleShading = 0.2f;

		/* Depth Stencil */
		B1 enableDepthStencil = true;
		B1 enableDepthWrite = true;
		RStencilCompareOp compareOp = RStencilCompareOp::STENCIL_COMPARE_OP_LESS;
		B1 enableBoundsTest = false;
		B1 enableDepthStencilTests = false;

		/* Color Blend */
		ARRAY<RColorBlendState> blendStates;
		ARRAY<RColorComponent> colorComponents;
		B1 enableColorBlendLogicOp = false;
		RLogicOp blendLogicOp = RLogicOp::LOGIC_OP_COPY;
		ARRAY<F32> blendConstants = {
			0.0f, 0.0f, 0.0f, 0.0f /* R, G, B, A */
		};

		/* Dynamic State */
		B1 enableDynamicState = false;
	};

	/*
	 Renderer Pipeline Object
	 Pipeline objects consists all the necessary data to be passed to the shader (Vertex inputs, resource 
	 descriptors).
	*/
	class DMK_API RPipelineObject {
	public:
		RPipelineObject() {}
		virtual ~RPipelineObject() {}

		virtual void initialize(RCoreObject* pCoreObject, RPipelineCreateInfo createInfo, RPipelineUsage usage) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_PIPELINE_OBJECT_H
