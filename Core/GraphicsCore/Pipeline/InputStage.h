// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/VertexBufferObject.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Pipeline Primitive Topology enum.
		 * Topology defines how the primitive is drawn.
		 */
		enum class PrimitiveTopology : UI8 {
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
		 * Input Stage of the grahics pipeline.
		 * This stage submits data to be rendered (vertex and index). It also defines how the input data should be
		 * handled by the GPU.
		 */
		class InputStage {
		public:
			InputStage() {}
			~InputStage() {}

			void SetTopology(PrimitiveTopology topology) { mTopology = topology; }
			PrimitiveTopology GetTopology() const { return mTopology; }

			void SetVertexBufferObject(const VertexBufferObject& object) { mVertexBufferObject = object; }
			VertexBufferObject& GetVertexBufferObject() { return mVertexBufferObject; }

		public:
			VertexBufferObject mVertexBufferObject = {};
			std::vector<UI32> mIndexBufferObject = {};	// TODO

			PrimitiveTopology mTopology = PrimitiveTopology::TRIANGLE_LIST;
		};
	}
}