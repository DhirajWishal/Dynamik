// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_COMMAND_H
#define _DYNAMIK_THREAD_COMMAND_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "Core/Macros/Global.h"

namespace Dynamik
{
	/* Thread command types */
	enum class DMK_API DMKThreadCommandType {
		DMK_THREAD_COMMAND_TYPE_UNDEFINED,
		DMK_THREAD_COMMAND_TYPE_TERMINATE,
		DMK_THREAD_COMMAND_TYPE_RESET,
		DMK_THREAD_COMMAND_TYPE_SYSTEM,
		DMK_THREAD_COMMAND_TYPE_SYNC,
	};

	/*
	 Thread Command for the Dynamik Engine
	 Data requests, submitions and synchronizing commands are sent using this object.
	*/
	class DMK_API DMKThreadCommand {
	public:
		DMKThreadCommand(DMKThreadCommandType ty) : type(ty) {}
		virtual ~DMKThreadCommand() {}

		DMKThreadCommandType type = DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM;
		B1 isHandled = false;
	};

	/*
	 Thread termination command
	*/
	class DMK_API DMKThreadTerminationCommand : public DMKThreadCommand {
	public:
		DMKThreadTerminationCommand() : DMKThreadCommand(DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_TERMINATE) {}
		~DMKThreadTerminationCommand() {}
	};

	/*
	 Reset command
	*/
	class DMK_API DMKThreadResetCommand : public DMKThreadCommand {
	public:
		DMKThreadResetCommand() : DMKThreadCommand(DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_RESET) {}
		virtual ~DMKThreadResetCommand() {}
	};

	/*
	 System command
	*/
	class DMK_API DMKThreadSystemCommand : public DMKThreadCommand {
	public:
		DMKThreadSystemCommand() : DMKThreadCommand(DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYSTEM) {}
		virtual ~DMKThreadSystemCommand() {}
	};

	/*
	 Synchronize command
	*/
	class DMK_API DMKThreadSyncCommand : public DMKThreadCommand {
	public:
		DMKThreadSyncCommand() : DMKThreadCommand(DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SYNC) {}
		virtual ~DMKThreadSyncCommand() {}
	};
}

#endif // !_DYNAMIK_THREAD_COMMAND_H
