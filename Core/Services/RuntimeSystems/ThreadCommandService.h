// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_COMMAND_SERVICE_H
#define _DYNAMIK_THREAD_COMMAND_SERVICE_H

#include "Core/Types/StaticArray.h"
#include "Core/Types/StaticQueue.h"

#include <vector>
#include <mutex>
#include <queue>

#define MAX_COMMANDS_PER_THREAD     10

inline std::mutex __globalThreadCommandMutex;

/*
 Interface command array structure.
*/
struct DMK_API ICommandQueue {};

/*
 Command Array Container.
*/
template<class TYPE>
struct DMK_API SCommandQueueContainer : public ICommandQueue {
	SCommandQueueContainer() {}
	~SCommandQueueContainer() {}

	std::queue<TYPE> commandQueue;
};

/*
 Dynamik Thread Command Service
 This object is allocated per thread and it manages all the thread command transactions.
*/
class DMK_API DMKThreadCommandService {
public:
	DMKThreadCommandService() {}
	~DMKThreadCommandService() {}

	/*
	 Check if a command is already registered.
	*/
	template<class COMMAND>
	DMK_FORCEINLINE bool isRegistered()
	{
		std::lock_guard<std::mutex> _lock(__globalThreadCommandMutex);
		STRING name = typeid(COMMAND).name();

		for (auto itr = registeredCommands.begin(); itr != registeredCommands.end(); itr++)
			if (*itr == name)
				return true;

		return false;
	}

	/*
	 Register a new component to the service.
	 If the component is already available, it does not do anything.
	*/
	template<class COMMAND>
	DMK_FORCEINLINE void registerCommand()
	{
		if (isRegistered<COMMAND>())
			return;

		std::lock_guard<std::mutex> _lock(__globalThreadCommandMutex);
		STRING name = typeid(COMMAND).name();

		commandMap[name] = StaticAllocator<SCommandQueueContainer<COMMAND>>::allocate();
		registeredCommands.push_back(name);
	}

	/*
	 Get the command queue of a given queue.
	*/
	template<class COMMAND>
	DMK_FORCEINLINE SCommandQueueContainer<COMMAND>* getCommandQueue()
	{
		if (!isRegistered<COMMAND>())
			registerCommand<COMMAND>();

		std::lock_guard<std::mutex> _lock(__globalThreadCommandMutex);
		STRING name = typeid(COMMAND).name();

		return Cast<SCommandQueueContainer<COMMAND>*>(commandMap[name]);
	}

	/*
	 Get the next pending command name.
	*/
	const STRING getNextCommandName()
	{
		std::lock_guard<std::mutex> _lock(__globalThreadCommandMutex);
		auto name = commandList.front();
		commandList.pop();

		return name;
	}

	/*
	 Get the front element of the command queue and pop it from the queue.
	*/
	template<class COMMAND>
	DMK_FORCEINLINE COMMAND getCommand()
	{
		auto commandQueue = getCommandQueue<COMMAND>();

		std::lock_guard<std::mutex> _lock(__globalThreadCommandMutex);
		auto command = commandQueue->commandQueue.front();
		commandQueue->commandQueue.pop();

		return command;
	}

	/*
	 Check if a command can be issued.
	*/
	template<class COMMAND>
	DMK_FORCEINLINE bool canIssueCommand()
	{
		return getCommandQueue<COMMAND>()->commandQueue.size() < MAX_COMMANDS_PER_THREAD;
	}

	/*
	 Issue a command to the command queue.

	 @param command: The command values.
	*/
	template<class COMMAND>
	DMK_FORCEINLINE void issueCommand(const COMMAND& command)
	{
		auto commandQueue = getCommandQueue<COMMAND>();

		while (getPendingCommandCount() >= MAX_COMMANDS_PER_THREAD);

		std::lock_guard<std::mutex> _lock(__globalThreadCommandMutex);
		STRING name = typeid(COMMAND).name();
		commandQueue->commandQueue.push(command);

		commandList.push(name);
	}

	/*
	 Get the count of the pending command list.
	*/
	const UI64 getPendingCommandCount() const { return commandList.size(); }

	/*
	 Issue a control command.
	*/
	void issueControlCommand(DMKThreadControlCommand controlCommand) { this->controlCommand = controlCommand; }

	/*
	 Get the issued control command.
	*/
	const DMKThreadControlCommand getControlCommand() const { return controlCommand; }

private:
	std::unordered_map<STRING, ICommandQueue*> commandMap;
	std::vector<STRING> registeredCommands;
	std::queue<STRING> commandList;
	DMKThreadControlCommand controlCommand = DMKThreadControlCommand::DMK_THREAD_CONTROL_COMMAND_UNDEFINED;
};

#endif // !_DYNAMIK_THREAD_COMMAND_SERVICE_H
