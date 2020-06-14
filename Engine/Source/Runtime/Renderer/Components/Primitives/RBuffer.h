// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_BUFFER_H
#define _DYNAMIK_RENDERER_BUFFER_H

/*
 Author:	Dhiraj WIshal
 Date:		14/06/2020
*/
#include "../RCoreObject.h"
#include "../PrimitiveTypeDefs.h"

namespace Dynamik
{
	/*
	 Renderer Buffer
	*/
	class DMK_API RBuffer {
	public:
		RBuffer() {}
		virtual ~RBuffer() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, BufferType eType, UI64 size) = 0;
		virtual void initialize(POINTER<RCoreObject> pCoreObject) = 0;

		virtual void setData(POINTER<RCoreObject> pCoreObject, UI64 size, UI64 offset, VPTR data) = 0;
		virtual VPTR getData(POINTER<RCoreObject> pCoreObject, UI64 size, UI64 offset) { return nullptr; }

		virtual UI64 getSize() { return size; }
		virtual BufferType getType() { return type; }

	protected:
		UI64 size = 0;
		BufferType type = BufferType::BUFFER_TYPE_VERTEX;
	};
}

#endif // !_DYNAMIK_RENDERER_BUFFER_H
