#pragma once
#ifndef _DYNAMIK_THREAD_COMMAND_H
#define _DYNAMIK_THREAD_COMMAND_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/


namespace Dynamik
{
	enum class DMK_API DMKThreadCommandType {
		DMK_THREAD_COMMAND_TYPE_SUBMIT,
		DMK_THREAD_COMMAND_TYPE_REQUEST,
		DMK_THREAD_COMMAND_TYPE_SYNC,
	};

	/*
	 Thread Command for the Dynamik Engine
	 Data requests, submitions and synchronizing commands are sent using this object.
	*/
	class DMK_API DMKThreadCommand {
		DMKThreadCommand(DMKThreadCommandType ty) : type(ty) {}
		virtual ~DMKThreadCommand() {}

		DMKThreadCommandType type = DMKThreadCommandType::DMK_THREAD_COMMAND_TYPE_SUBMIT;
	};
}

#endif // !_DYNAMIK_THREAD_COMMAND_H
