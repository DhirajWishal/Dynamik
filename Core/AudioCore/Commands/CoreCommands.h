// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace DMK
{
	namespace AudioCore
	{
		namespace Commands
		{
			/**
			 * Initialize Backend command.
			 * This initializes the required audio backend.
			 */
			struct InitializeBackend {
				InitializeBackend() = default;

				/**
				 * Construct the command by stating whether debugging should be enabled.
				 *
				 * @param enableDebugging: Boolean value stating whether or not to enable debugging.
				 */
				InitializeBackend(bool enableDebugging) : enableDebugging(enableDebugging) {}

				bool enableDebugging = true;	// Enable backend API debugging.
			};

			/**
			 * Terminate Backend command.
			 * This command terminates the audio backend.
			 */
			struct TerminateBackend { const bool __Terminate = true; };
		}
	}
}