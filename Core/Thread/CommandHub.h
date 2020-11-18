// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_COMMAND_HUB_H
#define _DYNAMIK_THREAD_COMMAND_HUB_H

namespace DMK
{
	namespace Thread
	{
		/**
		 * Command Hub is a special object which stores and submits commands to a specific thread.
		 */
		class CommandHub {
		public:
			/**
			 * Default constructor.
			 */
			CommandHub() {}

			/**
			 * Default destructor.
			 */
			virtual ~CommandHub() {}
		};
	}
}

#endif // !_DYNAMIK_THREAD_COMMAND_HUB_H
