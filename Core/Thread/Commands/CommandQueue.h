// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_COMMAND_QUEUE_H
#define _DYNAMIK_THREAD_COMMAND_QUEUE_H

#include "Command.h"
#include "Core/Types/StaticQueue.h"
#include <array>

#define THREAD_MAX_COMMAND_COUNT	10

namespace DMK
{
	namespace Threads
	{
		/**
		 * Command Queue for the Dynamik Engine.
		 * This object is used to store commands in a queue which is submitted to the thread.
		 *
		 * @tparam CommandCount: The maximum number of commands which can be stored.
		 */
		template<UI64 CommandCount = THREAD_MAX_COMMAND_COUNT>
		class CommandQueue {
		public:
			/**
			 * Default constructor.
			 */
			CommandQueue() {}

			/**
			 * Default destructor.
			 */
			~CommandQueue() {}

		private:
			StaticQueue<const char*, CommandCount> commandQueue;
		};
	}
}

#endif // !_DYNAMIK_THREAD_COMMAND_QUEUE_H
