// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include <mutex>
#include <queue>

#include "Managers/Thread/ThreadCommand.h"
#include "Core/Memory/StaticAllocator.h"

namespace Dynamik
{
	/*
	 Basic thread function.

	 @tparam THREAD: The system.
	*/
	template<class THREAD>
	void basicThreadFunction(std::queue<DMKThreadCommand*>* pCommandArray)
	{
		std::mutex _globalMutex;

		THREAD mySystem;
		UI64 index = 0;
		DMKThreadCommand* pCommand = nullptr;

	BEGIN:
		mySystem.onInitialize();

		do
		{
			/* Process commands */
			for (index = 0; index < pCommandArray->size(); index++)
			{
				/* Securely get the first element of the queue and pop it. */
				{
					std::lock_guard<std::mutex> _lock(_globalMutex);

					pCommand = pCommandArray->front();
					pCommandArray->pop();
				}

				/* To ensure that the main loop always gets updated */
				mySystem.onLoop();

				if (pCommand->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM)
				{
					mySystem.processCommand(pCommand);
				}
				else if (pCommand->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYNC)
				{

				}
				else if (pCommand->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_RESET)
				{
					goto BEGIN;
				}
				else if (pCommand->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_TERMINATE)
				{
					goto TERMINATE;
				}
				else if (pCommand->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_FORCE_TERMINATE)
				{
					std::terminate();
				}

				/* Deallocate handled command */
				StaticAllocator<DMKThreadCommand>::rawDeallocate(pCommand, 0);
			}

			mySystem.onLoop();
		} while (true);

	TERMINATE:
		for (UI64 index = 0; index < pCommandArray->size(); index++)
		{
			std::lock_guard<std::mutex> _lock(_globalMutex);

			pCommand = pCommandArray->front();
			pCommandArray->pop();

			StaticAllocator<DMKThreadCommand>::rawDeallocate(pCommand, 0);
		}

		mySystem.onTermination();
	}
}