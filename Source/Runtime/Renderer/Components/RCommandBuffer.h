// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_COMMAND_BUFFER_H
#define _DYNAMIK_RENDERER_COMMAND_BUFFER_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "Context/RFrameBuffer.h"
#include "RPipelineObject.h"
#include "Primitives/RBuffer.h"

namespace Dynamik
{
	class DMK_API RPipelineObject;

	/*
	 Renderer Command Buffer
	*/
	class DMK_API RCommandBuffer {
	public:
		RCommandBuffer() {}
		virtual ~RCommandBuffer() {}

		virtual void begin() = 0;

		virtual void bindVertexBuffer(RBuffer* pBuffer, UI64 firstBinding) = 0;
		virtual void bindIndexBuffer(RBuffer* pBuffer) = 0;

		/*
		 Bind pipeline and resources
		*/
		virtual void bindGraphicsPipeline(RPipelineObject* pPipelineObject) = 0;
		virtual void drawIndexed(UI64 firstIndex, UI64 vertexOffset, UI64 indexCount, UI64 instanceCount) = 0;
		virtual void drawVertexes(UI64 vertexIndex, UI64 vertexCount, UI64 instanceCount) = 0;
		virtual void end() = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_COMMAND_BUFFER_H
