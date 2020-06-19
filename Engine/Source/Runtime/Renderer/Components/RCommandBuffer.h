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

namespace Dynamik
{
	/*
	 Renderer Command Buffer
	*/
	class DMK_API RCommandBuffer {
	public:
		RCommandBuffer() {}
		virtual ~RCommandBuffer() {}

		virtual void begin() = 0;
		/*
		 Bind pipeline and resources
		*/
		virtual void bindPipeline(POINTER<RPipelineObject> pPipelineObject) = 0;
		virtual void end() = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_COMMAND_BUFFER_H
