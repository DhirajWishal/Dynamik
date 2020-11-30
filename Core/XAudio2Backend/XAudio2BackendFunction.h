// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Thread/Commands/CommandQueue.h"

namespace DMK
{
	namespace XAudio2Backend
	{
		/**
		 * XAudio2 Backend Function.
		 * This function enables the XAudio2Backend module to be executed on another thread. The function is
		 * executed by the Audio engine.
		 */
		void XAudio2BackendFunction(Thread::CommandQueue<THREAD_MAX_COMMAND_COUNT>* pCommandQueue);
	}
}