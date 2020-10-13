// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_QUEUE_H
#define _DYNAMIK_STATIC_QUEUE_H

#include "StaticArray.h"
#include "Core/Error/ErrorManager.h"

/*
 Static Queue for the Dynamik Engine
 This is a FIFO structure which uses a static array to store data. This means that there is an upper limit to the
 amount of data it can hold.

 @tparam TYPE: The type of the data which it holds.
 @tparam DataCount: The maximum amount of data this queue can hold.
*/
template<class TYPE, UI64 DataCount>
class DMK_API StaticQueue {
public:
	/*
	 Default constructor.
	*/
	StaticQueue() : currentDataCount(0U) {}
	~StaticQueue() {}

	/*
	 Push a data to the queue.
	 If the data requested to be added is grater than the stored amount, an error will be issued and the command
	 will be terminated without altering the queue.

	 @param data: The data to be added.
	*/
	void push(const TYPE& data)
	{
		if (currentDataCount > DataCount)
		{
			DMKErrorManager::logError("The queue is at maximum capacity!");
			return;
		}

		sMyData[currentDataCount - 1] = data;
	}

	/*
	 Push a data to the queue.
	 If the data requested to be added is grater than the stored amount, an error will be issued and the command
	 will be terminated without altering the queue.

	 @param data: The data to be added.
	*/
	void push(TYPE&& data)
	{
		push(Cast<const TYPE&>(data));
	}

	/*
	 Get the front element of the queue.
	*/
	const TYPE front() const
	{
		return sMyData[0];
	}

	/*
	 Get the front element of the queue.
	 The returned value can be modified.
	*/
	TYPE& front()
	{
		return sMyData[0];
	}

	/*
	 Pop/ remove the front element of the queue.
	 This is somewhat slow as the queue will get updated (O(n) -> (n = Data Count)).
	*/
	void pop()
	{
		currentDataCount--;
		_packData();
	}

	/*
	 Get the number of data stored.
	*/
	const UI64 size() const { return currentDataCount; }

	/*
	 Get the total capacity of the queue.
	*/
	constexpr UI64 capacity() const { return DataCount; }

private:	/* Helper Functions */
	/*
	 Pack the data.
	*/
	DMK_FORCEINLINE void _packData()
	{
		for (UI64 index = 1; index < DataCount; index++)
			sMyData[index - 1] = sMyData[index];
	}

private:
	StaticArray<TYPE, DataCount> sMyData;
	UI64 currentDataCount = 0;
};

#endif // !_DYNAMIK_STATIC_QUEUE_H

