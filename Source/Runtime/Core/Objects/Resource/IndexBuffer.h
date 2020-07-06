// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_INDEX_BUFFER_H
#define _DYNAMIK_INDEX_BUFFER_H

#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Interface Index Buffer
	 Base class for the Dynamik Index Buffer.
	*/
	class DMK_API I_IndexBuffer {
	public:
		I_IndexBuffer() = default;
		virtual ~I_IndexBuffer() = default;

		DMK_FORCEINLINE virtual void add(const UI64& index) = 0;
		DMK_FORCEINLINE virtual const VPTR data() const = 0;
		DMK_FORCEINLINE virtual const UI64 size() const = 0;
		DMK_FORCEINLINE virtual const UI64 typeSize() const = 0;
	};

	/*
	 Dynamik Index Buffer
	*/
	template<class INDEX>
	class DMK_API DMKIndexBuffer : public I_IndexBuffer {
	public:
		DMKIndexBuffer() = default;
		~DMKIndexBuffer() = default;

		DMK_FORCEINLINE virtual void add(const UI64& index) override final
		{
			buffer.pushBack((INDEX)index);
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
		ARRAY<INDEX> buffer;
	};
}

#endif // !_DYNAMIK_INDEX_BUFFER_H
