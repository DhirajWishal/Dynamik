// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/RenderTargetHandle.h"
#include "GraphicsCore/Objects/ShaderCode.h"
#include "GraphicsCore/Backend/ViewPort.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Pipeline Type enum.
		 */
		enum class PipelineType : UI8 {
			UNDEFINED,		// Undefined pipeline.
			GRAPHICS,		// Raster Graphics
			COMPUTE,		// Compute 
			RAY_TRACING,	// Ray Tracing (only if the device is supported).
		};

		/**
		 * Pipeline Primitive Topology enum.
		 */
		enum class PipelinePrimitiveTopology : UI8 {
			POINT_LIST,
			LINE_LIST,
			LINE_STRIP,
			TRIANGLE_LIST,
			TRIANGLE_STRIP,
			TRIANGLE_FAN,
			LINE_LIST_WITH_ADJACENCY,
			LINE_STRIP_WITH_ADJACENCY,
			TRIANGLE_LIST_WITH_ADJACENCY,
			TRIANGLE_STRIP_WITH_ADJACENCY,
			PATCH_LIST,
		};

		/**
		 * Pipeline Cull Mode enum.
		 */
		enum class PipelineCullMode : UI8 {
			NONE,
			FRONT,
			BACK,
			FRONT_AND_BACK,
		};

		/**
		 * Pipeline Primitive Front Face enum.
		 * The front face determines the front side of a given triangle.
		 */
		enum class PipelinePrimitiveFrontFace : UI8 {
			COUNTER_CLOCKWISE,
			CLOCKWISE,
		};

		/**
		 * Pipeline Polygon Mode enum.
		 */
		enum class PipelinePolygonMode : UI8 {
			FILL,
			LINE,
			POINT,
			FILL_RECTANGLE,
		};

		/**
		 * Input Assembly Specification structure.
		 */
		struct InputAssemblySpecification {
			PipelinePrimitiveTopology mPrimitiveTopology = PipelinePrimitiveTopology::TRIANGLE_LIST;

			bool mEnablePrimitiveRestart = false;

			bool operator==(const InputAssemblySpecification& spec) const
			{
				return mPrimitiveTopology == spec.mPrimitiveTopology
					&& mEnablePrimitiveRestart == spec.mEnablePrimitiveRestart;
			}
		};

		/**
		 * Tessellation Specification structure.
		 */
		struct TessellationSpecification {
			UI32 mControlPointCount = 0;

			bool operator==(const TessellationSpecification& spec) const
			{
				return mControlPointCount == spec.mControlPointCount;
			}
		};

		/**
		 * Rasterizer Specification strucuture.
		 */
		struct RasterizerSpecification {
			float mPrimitiveLineWidth = 1.0f;
			float mDepthBiasFactor = 1.0f;
			float mDepthSlopeFactor = 1.0f;

			PipelineCullMode mCullMode = PipelineCullMode::NONE;
			PipelinePrimitiveFrontFace mFrontFace = PipelinePrimitiveFrontFace::COUNTER_CLOCKWISE;
			PipelinePolygonMode mPolygonMode = PipelinePolygonMode::FILL;

			bool mEnableDepthClamp = false;
			bool mEnableDepthBias = false;
			bool mEnableDiscard = false;

			bool operator==(const RasterizerSpecification& spec) const
			{
				return mPrimitiveLineWidth == spec.mPrimitiveLineWidth
					&& mDepthBiasFactor == spec.mDepthBiasFactor
					&& mDepthSlopeFactor == spec.mDepthSlopeFactor
					&& mCullMode == spec.mCullMode
					&& mFrontFace == spec.mFrontFace
					&& mPolygonMode == spec.mPolygonMode
					&& mEnableDepthClamp == spec.mEnableDepthClamp
					&& mEnableDepthBias == spec.mEnableDepthBias
					&& mEnableDiscard == spec.mEnableDiscard;
			}
		};

		/**
		 * Multisampling Specification structure.
		 */
		struct MultisamplingSpecification {
			float mMinSampleShading = 0.0f;

			bool mEnableSampleShading = false;
			bool mEnableAlphaToCoverage = false;
			bool mEnableAlphaToOne = false;

			bool operator==(const MultisamplingSpecification& spec) const
			{
				return mMinSampleShading == spec.mMinSampleShading
					&& mEnableSampleShading == spec.mEnableSampleShading
					&& mEnableAlphaToCoverage == spec.mEnableAlphaToCoverage
					&& mEnableAlphaToOne == spec.mEnableAlphaToOne;
			}
		};

		/**
		 * Depth Stencil Specification structure.
		 */
		struct DepthStencilSpecification {
			float mMaxBound = 1.0f;
			float mMinBound = 0.0f;

			CompareOperator mComareOperator = CompareOperator::DONT_COMPARE;

			bool mEnableTest = false;
			bool mEnableStencilTest = false;
			bool mEnableWriteTest = false;
			bool mEnableBoundTests = false;

			bool operator==(const DepthStencilSpecification& spec) const
			{
				return mMaxBound == spec.mMaxBound
					&& mMinBound == spec.mMinBound
					&& mComareOperator == spec.mComareOperator
					&& mEnableTest == spec.mEnableTest
					&& mEnableStencilTest == spec.mEnableStencilTest
					&& mEnableWriteTest == spec.mEnableWriteTest
					&& mEnableBoundTests == spec.mEnableBoundTests;
			}
		};

		/**
		 * Color Blend Specification structure.
		 */
		struct ColorBlendSpecification {
			float mBlendConstants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };	// R, G, B, A

			LogicOperator mLogicalOperator = LogicOperator::CLEAR;

			bool mEnable = false;

			bool operator==(const ColorBlendSpecification& spec) const
			{
				return mLogicalOperator == spec.mLogicalOperator
					&& mEnable == spec.mEnable
					&& mBlendConstants[0] == spec.mBlendConstants[0]
					&& mBlendConstants[1] == spec.mBlendConstants[1]
					&& mBlendConstants[2] == spec.mBlendConstants[2]
					&& mBlendConstants[3] == spec.mBlendConstants[3];
			}
		};

		/**
		 * Pipeline Specification structure.
		 * This structure defines how a pipeline should be initialized.
		 */
		struct PipelineSpecification {
			std::vector<ShaderCode> mShaders;
			RenderTargetHandle mRenderTargetHandle = {};
			ViewPort mViewPort = {};

			InputAssemblySpecification mInputAssemblySpec = {};
			TessellationSpecification mTessellationSpec = {};
			RasterizerSpecification mRasterizerSpec = {};
			MultisamplingSpecification mMultisamplingSpec = {};
			DepthStencilSpecification mDepthStencilSpec = {};
			ColorBlendSpecification mColorBlendSpec = {};

			PipelineType mType = PipelineType::UNDEFINED;	// Pipeline type.

		public:
			bool operator==(const PipelineSpecification& spec) const
			{
				return mShaders == spec.mShaders
					&& mType == spec.mType
					&& mRenderTargetHandle == spec.mRenderTargetHandle
					&& mViewPort == spec.mViewPort
					&& mType == spec.mType
					&& mInputAssemblySpec == spec.mInputAssemblySpec
					&& mTessellationSpec == spec.mTessellationSpec
					&& mRasterizerSpec == spec.mRasterizerSpec
					&& mMultisamplingSpec == spec.mMultisamplingSpec
					&& mDepthStencilSpec == spec.mDepthStencilSpec
					&& mColorBlendSpec == spec.mColorBlendSpec;
			}
		};
	}
}