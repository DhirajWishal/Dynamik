// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_INDEX_BUFFER_H
#define _DYNAMIK_INDEX_BUFFER_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

namespace Dynamik
{
	/*
	 Dynamik Index Buffer
	 In this structure users can specify the index size of the index buffer.
	 The required size is to be set in bytes.

	 The buffer is dynamically re-sizable.
	*/
	class DMK_API DMKIndexBuffer {
	public:
		DMKIndexBuffer() {}
		~DMKIndexBuffer() {}

		/*
		 Set the index size of the current buffer. 
		 If an index size is set and no data are added or initialized, the resize will be successful. But if data are added
		 or is initialized, the resize will be ignored. To accomplish this task, use the resize(UI64) method.

		 The maximum index size supported is 8 (64 bits).

		 @param size: The byte size of the index. Default is 4 bytes (32 bit).
		*/
		void setIndexSize(UI64 size = 4);

		/*
		 Get the index byte size.
		*/
		const UI64 getIndexSize() const;

		/*
		 Initialize the buffer with the exact number of indexes. 
		 This method will allocate the buffer and the buffer with a definite index size. The buffer is re-sizable even
		 though the buffer is initialized prior to adding data beyond the allocated amount.

		 @warn: The index size must be set before calling this method.

		 @param indexCount: The index count to initialize the buffer to.
		*/
		void initialize(UI64 indexCount);

		/*
		 Clears the buffer by deallocating the whole memory block used by the buffer.
		*/
		void clear();

		/*
		 Add an index to the index buffer. 
		 The method accepts a 64 bit unsigned integers but the data that will be added to the buffer will be 
		 (index size * 8) bit unsigned integers. Which means that the 64 bit integer will be reduced to the or used 
		 depending on the index size.

		 @param index: The index value.
		*/
		void add(const UI64& index);

		/*
		 Set data to a specific location in the index buffer. 

		 @param data: The pointer to the data location.
		 @param size: The byte size of the data.
		 @param offset: The offset to the location. Default is 0.
		*/
		void set(const VPTR data, UI64 size, UI64 offset = 0);

		/*
		 Return the data address (memory block pointer) of the buffer.
		*/
		VPTR data() const;

		/*
		 Return the size of the buffer. 
		 @return: indexSize * indexCount;
		*/
		const UI64 size() const;

		/* THIS FUNCTION CURRENTLY DOES NOT CARRY OUT ANY FUNCTIONALITY! 
		 Resize the index buffer. 
		 This function will resize the index size and re initializes the buffer with the stored data. If the buffer is 
		 not initialized or doesn't have data, this method will only update the indexSize private variable.

		 @param newIndexSize: The new size of the index in bytes.
		*/
		void resize(UI64 newIndexSize);

		/*
		 Get an index value at a given memory index. 
		 This method will return a pointer to the memory block containing the index value but the user can cast it to any
		 other integer type to get the right value. The returned value can be modified.

		 @param index;
		*/
		VPTR at(I64 index);

		/*
		 Get an index value at a given memory index. 
		 This method will return a pointer to the memory block containing the index value but the user can cast it to any
		 other integer type to get the right value. The returned value cannot be modified.

		 @param index;
		*/
		const VPTR at(I64 index) const;

	private:	/* Helper Functions */
		/*
		 Grow the buffer by adding a byte size to the last allocation size.

		 @param byteSize: The size to be added.
		*/
		void _growBuffer(UI64 byteSize);

	private:
		UI64 indexSize = 0;
		UI64 indexCount = 0;
		UI64 lastAllocationSize = 0;
		VPTR pDataStore = nullptr;
	};
}

#endif // !_DYNAMIK_INDEX_BUFFER_H
