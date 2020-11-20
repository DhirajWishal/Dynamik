// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Commands/CommandQueue.h"

#include <thread>
#include <queue>

namespace DMK
{
	namespace Threads
	{
		/**
		 * Thread handle for the Dynamik Engine.
		 * This object is used to store and manage a single thread object.
		 * Different commands to the running threads are submitted through this object.
		 */
		class ThreadHandle {
		public:
			/**
			 * Default constructor.
			 */
			ThreadHandle() {}

			/**
			 * Default destructor.
			 */
			virtual ~ThreadHandle() {}

			/**
			 * Initialize the thread.
			 * This method initialized the thread object.
			 */
			virtual void InitializeThread() {}

			/**
			 * Terminate the thread.
			 * This method terminates the thread object.
			 */
			virtual void TerminateThread() {}

		protected:
			/**
			 * Submit a command to the thread handle.
			 *
			 * @param command: The command to be submitted.
			 * @tparam Type: The type of the command.
			 */
			template<class Type>
			DMK_FORCEINLINE void SubmitCommand(const Type& command)
			{
			}

		private:

		protected:
			std::thread mThread = {};	// The thread object.
		};
	}
}
