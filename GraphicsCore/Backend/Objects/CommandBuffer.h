// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_COMMAND_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_COMMAND_BUFFER_H

#include "GraphicsCore/Backend/Objects/VertexBuffer.h"
#include "GraphicsCore/Backend/Objects/IndexBuffer.h"
#include "GraphicsCore/Backend/Objects/StaggingBuffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Command Buffer Level.
		 */
		enum class CommandBufferLevel {
			COMMAND_BUFFER_LEVEL_PRIMARY,
			COMMAND_BUFFER_LEVEL_SECONDARY,
		};

		/**
		 * Command Buffer for Dynamik Graphics Engine.
		 * This object stores all the commands which are to be submitted to the GPU.
		 */
		class CommandBuffer : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			CommandBuffer() {}

			/**
			 * Default destructor.
			 */
			virtual ~CommandBuffer() {}

			/**
			 * Inherits this buffer from another command buffer and makes it ready to record commands.
			 *
			 * @param pCommandBuffer: The command buffer object pointer to be inherited from.
			 */
			virtual void InheritFrom(CommandBuffer* pCommandBuffer) {}

			/**
			 * Bind a vertex buffer to the command.
			 *
			 * @param pVertexBuffer: The vertex buffer pointer.
			 */
			virtual void BindVertexBuffer(VertexBuffer* pVertexBuffer) {}

			/**
			 * Bind an index buffer to the command.
			 *
			 * @param pIndexBuffer: The index buffer pointer.
			 */
			virtual void BindIndexBuffer(IndexBuffer* pIndexBuffer) {}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_COMMAND_BUFFER_H
