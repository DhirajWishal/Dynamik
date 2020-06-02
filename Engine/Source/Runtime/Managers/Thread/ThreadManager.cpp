#include "dmkafx.h"
#include "ThreadManager.h"

#include "Renderer/Renderer.h"

#include <mutex>

namespace Dynamik
{
	std::mutex _globalMutex;

	/*
	 Runtime thread function.
	 These threads are permanent and will only be terminated upon engine termination.

	 @tparam THREAD: The system.
	 @param commandPoolPtr: Pointer to the shared command pool.
	*/
	template<class THREAD>
	void _runtimeThread(POINTER<DMKThreadManager::ThreadCommandBuffer> commandPoolPtr)
	{
		THREAD mySystem;
		UI64 index = 0;

	BEGIN:
		mySystem.initialize();

		do
		{
			/* Process commands */
			if (commandPoolPtr->commands.size() && !commandPoolPtr->hasExcuted)
			{
				for (index = 0; index < commandPoolPtr->commands.size(); index++)
				{
					/* To ensure that the main loop always gets updated */
					mySystem.onLoop();

					if (commandPoolPtr->commands.at(index)->isHandled)
						continue;
					commandPoolPtr->commands.at(index)->isHandled = true;

					if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM)
					{
						mySystem.processCommand(commandPoolPtr->commands.at(index));
					}
					else if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYNC)
					{

					}
					else if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_RESET)
					{
						goto BEGIN;
					}
					else if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_TERMINATE)
					{
						goto TERMINATE;
					}
				}

				commandPoolPtr->hasExcuted = true;
			}

			mySystem.onLoop();
		} while (true);

	TERMINATE:
		mySystem.onTermination();
	}

	/*
	 Get the usabe total thread count
	*/
	UI32 DMKThreadManager::getUseableThreadCount()
	{
		return std::thread::hardware_concurrency();
	}

	/*
	 Initialize all the runtime threads
	*/
	void DMKThreadManager::initializeBasicThreads()
	{
		/* Initialize the rendering thread */
		myRendererThread.type = DMKThreadType::DMK_THREAD_TYPE_RENDERER;
		myRendererThread.thread.swap(std::thread(_runtimeThread<DMKRenderer>, &myRendererThread.commandBuffer));
	}

	/*
	 Clear all thread commands. If a thread has not completed all, that thread is skipped.
	*/
	void DMKThreadManager::clearCommands()
	{
		/* Clear runtime thread commands */

		/* Rendering thread */
		if (myRendererThread.commandBuffer.hasExcuted)
		{
			for (auto _command : myRendererThread.commandBuffer.commands)
				StaticAllocator<DMKThreadCommand>::deallocate(_command, 0);

			myRendererThread.commandBuffer.commands.clear();
		}
	}

	/* ////////// Renderer Thread Commands \\\\\\\\\\ */
	void DMKThreadManager::issueSamplesCommandRT(DMKSampleCount const& samples)
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_SET_SAMPLES);
		_command.data = (DMKSampleCount*)&samples;

		_pushToThread(_command);
	}

	void DMKThreadManager::issueWindowHandleCommandRT(const POINTER<DMKWindowHandle>& handle)
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_SET_WINDOW_HANDLE);
		_command.data = handle.get();

		_pushToThread(_command);
	}

	void DMKThreadManager::issueInitializeCommandRT()
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE);

		_pushToThread(_command);
	}

	void DMKThreadManager::issueCreateContextCommandRT(DMKRenderContextType context, DMKViewport viewport)
	{
		RenderContextCommand _command;
		_command.contextType = context;
		_command.viewport = viewport;

		/* Push to command buffer */
		myRendererThread.commandBuffer.hasExcuted = false;
		myRendererThread.commandBuffer.commands.pushBack(new RenderContextCommand(_command));
	}

	void DMKThreadManager::issueInitializeObjectCommandRT()
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_OBJECTS);

		_pushToThread(_command);
	}

	void DMKThreadManager::issueInitializeFinalsCommandRT()
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS);

		_pushToThread(_command);
	}

	/*
	 Main thread function
	*/
	void DMKThreadManager::_threadFunction(POINTER<DMKThread> mySystem, POINTER<ThreadCommandBuffer> commandPoolPtr)
	{
		UI64 index = 0;

	BEGIN:
		mySystem->initialize();

		do
		{
			/* Process commands */
			if (commandPoolPtr->commands.size() && !commandPoolPtr->hasExcuted)
			{
				for (index = 0; index < commandPoolPtr->commands.size(); index++)
				{
					if (commandPoolPtr->commands.at(index)->isHandled)
						continue;
					commandPoolPtr->commands.at(index)->isHandled = true;

					if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM)
					{
						mySystem->processCommand(commandPoolPtr->commands.at(index));
					}
					else if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYNC)
					{

					}
					else if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_RESET)
					{
						goto BEGIN;
					}
					else if (commandPoolPtr->commands.at(index)->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_TERMINATE)
					{
						goto TERMINATE;
					}
				}

				commandPoolPtr->hasExcuted = true;
			}

			mySystem->onLoop();
		} while (true);

	TERMINATE:
		mySystem->onTermination();

		/*
		 Deallocate the system since its allocated from heap.
		 Remove this if its allocated from the stack.
		*/
		StaticAllocator<DMKThread>::deallocate(mySystem, 0);
	}

	void DMKThreadManager::_pushToThread(DMKRendererCommand command)
	{
		myRendererThread.commandBuffer.hasExcuted = false;
		myRendererThread.commandBuffer.commands.pushBack(new DMKRendererCommand(command));
	}
}