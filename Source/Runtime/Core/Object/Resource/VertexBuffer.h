// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VERTEX_BUFFER_H
#define _DYNAMIK_VERTEX_BUFFER_H

/*
 Author:	Dhiraj Wishal
 Date:		24/06/2020
*/
#include "VertexObject.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Interface Vertex Buffer
	 Base class for the Dynamik Vertex Buffer.
	*/
	class DMK_API I_VertexBuffer {
	public:
		I_VertexBuffer() = default;
		virtual ~I_VertexBuffer() = default;

		DMK_FORCEINLINE virtual void add(const DMKVertexObject* pVertexObject) = 0;
		DMK_FORCEINLINE virtual const VPTR data() const = 0;
		DMK_FORCEINLINE virtual const UI64 size() const = 0;
		DMK_FORCEINLINE virtual const UI64 typeSize() const = 0;
	};

	/*
	 Dynamik Vertex Buffer
	*/
	template<class VERTEX>
	class DMK_API DMKVertexBuffer : public I_VertexBuffer {
	public:
		DMKVertexBuffer() {}
		~DMKVertexBuffer() {}

		DMK_FORCEINLINE virtual void add(const DMKVertexObject* pVertexObject) override final
		{
			buffer.pushBack(*((VERTEX*)pVertexObject.get()));
		}

		DMK_FORCEINLINE virtual const VPTR data() const override final
		{
			return buffer.data();
		}

		DMK_FORCEINLINE virtual const UI64 size() const override final
		{
			return buffer.size();
		}

		DMK_FORCEINLINE virtual const UI64 typeSize() const override final
		{
			return buffer.typeSize();
		}

	private:
		ARRAY<VERTEX> buffer;
	};
}

#endif // !_DYNAMIK_VERTEX_BUFFER_H
