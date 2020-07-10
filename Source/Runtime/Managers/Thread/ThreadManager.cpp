// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ThreadManager.h"

#include "Renderer/Renderer.h"

#include <mutex>

/* Maximum commands that can be in a command queue at runtime */
#define MAX_COMMANDS_IN_FLIGHT		10

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
	void _runtimeThread(DMKThreadManager::ThreadCommandBuffer* commandPoolPtr)
	{
		THREAD mySystem;
		UI64 index = 0;
		DMKThreadCommand* pCommand = nullptr;

	BEGIN:
		mySystem.initialize();

		do
		{
			/* Process commands */
			for (index = 0; index < commandPoolPtr->commands.size(); index++)
			{
				/* Securely get the first element of the queue and pop it. */
				{
					std::lock_guard<std::mutex> _lock(_globalMutex);

					pCommand = commandPoolPtr->commands.front();
					commandPoolPtr->commands.pop();
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
		mySystem.onTermination();
	}

	DMKThreadManager::~DMKThreadManager()
	{
	}

	/*
	 Get the usable total thread count
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
	}

	void DMKThreadManager::terminateAll()
	{
		/* Terminate Rendering Thread */
		myRendererThread.thread.join();
	}

	void DMKThreadManager::pushRendererCommand(DMKRendererCommand* pCommand)
	{
		/* Wait till all the submitted commands are executed. */
		while (myRendererThread.commandBuffer.commands.size() >= MAX_COMMANDS_IN_FLIGHT);

		myRendererThread.commandBuffer.commands.push(pCommand);
	}

	/* ////////// Renderer Thread Commands \\\\\\\\\\ */
	void DMKThreadManager::issueSamplesCommandRT(DMKSampleCount const& samples)
	{
		RendererSetSamplesCommand _command;
		_command.samples = samples;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererSetSamplesCommand>::allocateInit(_command));
	}

	void DMKThreadManager::issueWindowHandleCommandRT(const DMKWindowHandle* handle)
	{
		RendererSetWindowHandleCommand _command;
		_command.windowHandle = (DMKWindowHandle*)handle;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererSetWindowHandleCommand>::allocateInit(_command));
	}

	void DMKThreadManager::issueInitializeCommandRT()
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE);

		_pushToThread(_command);
	}

	void DMKThreadManager::issueCreateContextCommandRT(DMKRenderContextType context, DMKViewport viewport)
	{
		RendererCreateContextCommand _command;
		_command.contextType = context;
		_command.viewport = viewport;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererCreateContextCommand>::allocateInit(_command));
	}

	void DMKThreadManager::issueInitializeCameraCommandRT(DMKCameraModule* pModule)
	{
		RendererInitializeCamera _command;
		_command.pCameraModule = pModule;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererInitializeCamera>::allocateInit(_command));
	}

	void DMKThreadManager::issueInitializeEnvironmentMapCommandRT(DMKEnvironmentMap* pEnvironmentMap)
	{
		RendererInitializeEnvironmentMap _command;
		_command.pEnvironmentMap = pEnvironmentMap;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererInitializeEnvironmentMap>::allocateInit(_command));
	}

	void DMKThreadManager::issueInitializeEntityCommandRT(DMKGameEntity* meshComponents)
	{
		RendererAddEntity _command;
		_command.entity = meshComponents;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererAddEntity>::allocateInit(_command));
	}

	void DMKThreadManager::issueInitializeGameWorldCommandRT(DMKGameWorld* pGameWorld)
	{
		RendererInitializeGameWorld _command;
		_command.pGameWorld = pGameWorld;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererInitializeGameWorld>::allocateInit(_command));
	}

	void DMKThreadManager::issueInitializeFinalsCommandRT()
	{
		DMKRendererCommand _command(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS);

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<DMKRendererCommand>::allocateInit(_command));
	}

	void DMKThreadManager::issueRawCommandRT(RendererInstruction instruction)
	{
		DMKRendererCommand _command(instruction);

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<DMKRendererCommand>::allocateInit(_command));
	}

	void DMKThreadManager::issueFrameBufferResizeCommandRT(DMKExtent2D extent)
	{
		RendererResizeFrameBuffer _command;
		_command.windowExtent = extent;

		/* Push to command queue */
		pushRendererCommand(StaticAllocator<RendererResizeFrameBuffer>::allocateInit(_command));
	}

	void DMKThreadManager::issueTerminateCommand()
	{
		/* Terminate Renderer */
		{
			DMKRendererCommand _command1(RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_FRAME);

			/* Push to command queue */
			pushRendererCommand(StaticAllocator<DMKRendererCommand>::allocateInit(_command1));

			DMKRendererCommand _command2(RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_OBJECTS);

			/* Push to command queue */
			pushRendererCommand(StaticAllocator<DMKRendererCommand>::allocateInit(_command2));

			DMKRendererCommand _command3(RendererInstruction::RENDERER_INSTRUCTION_TERMINATE);

			/* Push to command queue */
			pushRendererCommand(StaticAllocator<DMKRendererCommand>::allocateInit(_command3));

			/* Issue complete termination */
			DMKThreadCommand _commandT(DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_TERMINATE);
			myRendererThread.commandBuffer.commands.push(StaticAllocator<DMKThreadCommand>::allocateInit(_commandT));

			/* Wait till the renderer thread is complete */
			myRendererThread.thread.join();
		}
	}

	/*
	 Main thread function
	*/
	void DMKThreadManager::_threadFunction(DMKThread* mySystem, ThreadCommandBuffer* commandPoolPtr)
	{
		UI64 index = 0;
		DMKThreadCommand* pCommand = nullptr;

	BEGIN:
		mySystem->initialize();

		do
		{
			/* Process commands */
			for (index = 0; index < commandPoolPtr->commands.size(); index++)
			{
				pCommand = commandPoolPtr->commands.front();
				commandPoolPtr->commands.pop();

				if (pCommand->type == DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM)
				{
					mySystem->processCommand(pCommand);
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

				StaticAllocator<DMKThreadCommand>::rawDeallocate(pCommand, 0);
			}

			mySystem->onLoop();
		} while (true);

	TERMINATE:
		mySystem->onTermination();

		/*
		 Deallocate the system since its allocated from heap.
		 Remove this if its allocated from the stack.
		*/
		StaticAllocator<DMKThread>::rawDeallocate(mySystem, 0);
	}

	void DMKThreadManager::_pushToThread(DMKRendererCommand command)
	{
		myRendererThread.commandBuffer.commands.push(StaticAllocator<DMKRendererCommand>::allocateInit(command));
	}
}