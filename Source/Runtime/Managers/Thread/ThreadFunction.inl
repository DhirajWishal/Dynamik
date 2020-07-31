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
	void basicThreadFunction(DMKThreadCommandService* pCommandService)
	{
		std::mutex _globalMutex;

		THREAD mySystem;
		mySystem.setupCommandService(pCommandService);
		UI64 index = 0;
		DMKThreadControlCommand commandType = DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_UNDEFINED;

	BEGIN:
		mySystem.onInitialize();

		do
		{
			/* Process commands */
			while (pCommandService->getPendingCommandCount())
			{
				/* To ensure that the main loop always gets updated */
				mySystem.onLoop();

				/* Process control instructions. */
				commandType = pCommandService->getControlCommand();

				if (commandType == DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_SYNC);
				else if (commandType == DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_RESET)
					goto BEGIN;
				else if (commandType == DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_TERMINATE)
					goto TERMINATE;
				else if (commandType == DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_FORCE_TERMINATE)
					std::terminate();

				/* Submit the command to the system. */
				mySystem.processCommand(pCommandService->getNextCommandName());
			}

			mySystem.onLoop();
		} while (true);

	TERMINATE:

		mySystem.onTermination();
	}
}