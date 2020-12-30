// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace DMK
{
	namespace Thread
	{
		/**
		 * Command Hub is a special object which stores and submits commands to a specific thread.
		 */
		class CommandHub {
		public:
			CommandHub() {}
			virtual ~CommandHub() {}
		};
	}
}
