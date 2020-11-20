// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Command.h"
#include "Core/Types/StaticQueue.h"

#include <mutex>

#define THREAD_MAX_COMMAND_COUNT	10

namespace DMK
{
	namespace Threads
	{
		// Command queue mutex.
		static std::mutex __CommandQueueMutex = {};

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

			/**
			 * Push a new command to the command queue.
			 * This method will wait till the command queue has an empty slot to push the data.
			 *
			 * @tparam Type: The type of the command.
			 * @param pState: The state variable pointer.
			 */
			template<class Type>
			void PushCommand(CommandState* pState = nullptr)
			{
				// Wait till the command queue has space.
				while (commandQueue.Size() >= CommandCount);

				// Lock the queue and push the data.
				std::lock_guard<std::mutex> _lock(__CommandQueueMutex);
				commandQueue.Push(std::make_pair(typeid(Type).name(), new Command<Type>(Type(), pState)));
			}

			/**
			 * Push a new command to the command queue.
			 * This method will wait till the command queue has an empty slot to push the data.
			 *
			 * @tparam Type: The type of the command.
			 * @param command: The command data to be pushed with. Default is Type().
			 * @param pState: The state variable pointer.
			 */
			template<class Type>
			void PushCommand(const Type& command, CommandState* pState = nullptr)
			{
				// Wait till the command queue has space.
				while (commandQueue.Size() >= CommandCount);

				// Lock the queue and push the data.
				std::lock_guard<std::mutex> _lock(__CommandQueueMutex);
				commandQueue.Push(std::make_pair(typeid(Type).name(), new Command<Type>(std::move(command), pState)));
			}

			/**
			 * Get the next command name from the queue.
			 *
			 * @return The const char pointer name.
			 */
			const char* GetCommandName() const
			{
				// Lock the queue and get the command name.
				std::lock_guard<std::mutex> _lock(__CommandQueueMutex);
				return commandQueue.Get().first;
			}

			/**
			 * Get the next command from the queue.
			 *
			 * @return CommandBase pointer.
			 */
			CommandBase* GetCommand() const
			{
				// Lock the queue and get the command.
				std::lock_guard<std::mutex> _lock(__CommandQueueMutex);
				return commandQueue.Get().second;
			}

			/**
			 * Get the first command and pop it from the queue.
			 *
			 * @return CommandBase pointer.
			 */
			CommandBase* GetAndPop()
			{
				// Lock the queue and get the command.
				std::lock_guard<std::mutex> _lock(__CommandQueueMutex);
				return commandQueue.GetAndPop().second;
			}

			/**
			 * Get the number of commands stored.
			 *
			 * @return The number of commands in the command queue.
			 */
			UI64 Count() const { return commandQueue.Size(); }

		private:
			StaticQueue<std::pair<const char*, CommandBase*>, CommandCount> commandQueue;	// Command Queue.
		};
	}
}
