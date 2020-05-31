#include "dmkafx.h"
#include "ThreadManager.h"

#include "Renderer/RendererThread.h"

#include <mutex>

namespace Dynamik
{
	std::mutex _globalMutex;

	UI32 DMKThreadManager::getUseableThreadCount()
	{
		return std::thread::hardware_concurrency();
	}

	void DMKThreadManager::initializeBasicThreads()
	{
		/* Initialize the rendering thread */
		myRendererThread.type = DMKThreadType::DMK_THREAD_TYPE_RENDERER;
		myRendererThread.thread.swap(std::thread(_threadFunction, new DMKRendererThread, &myRendererThread.threadCommands));

		/* Initialize the audio thread */

		/* Initialize the physics thread */
	}

	void DMKThreadManager::issueSamplesCommand(DMKSampleCount const& samples)
	{
		DMKRendererThreadCommand _command(RendererInstruction::RENDERER_INSTRUCTION_UPDATE_SET_SAMPLES);
		_command.data = (DMKSampleCount*)&samples;

		std::lock_guard<std::mutex> _lg(_globalMutex);
		myRendererThread.threadCommands.pushBack(&_command);
	}

	void DMKThreadManager::issueWindowHandleCommand(const POINTER<DMKWindowHandle>& handle)
	{
		DMKRendererThreadCommand _command(RendererInstruction::RENDERER_INSTRUCTION_UPDATE_SET_WINDOW_HANDLE);
		_command.data = handle.get();

		std::lock_guard<std::mutex> _lg(_globalMutex);
		myRendererThread.threadCommands.pushBack(&_command);
	}

	void DMKThreadManager::_threadFunction(POINTER<DMKThread> mySystem, POINTER<ARRAY<POINTER<DMKThreadCommand>>> commandPoolPtr)
	{
	BEGIN:
		mySystem->initialize();

		do
		{
			/* Process commands */
			if (commandPoolPtr->size())
			{
				for (auto _command : commandPoolPtr.dereference())
				{
					if (_command->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM)
					{
						mySystem->processCommand(_command);
					}
					else if (_command->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYNC)
					{

					}
					else if (_command->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_RESET)
					{
						goto BEGIN;
					}
					else { goto TERMINATE; }
				}

				/* clear the command pool */
				commandPoolPtr->clear();
			}

			mySystem->onLoop();
		} while (true);

	TERMINATE:
		mySystem->onTermination();
	}
}