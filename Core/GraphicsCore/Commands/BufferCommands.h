// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CommandBase.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			/**
			 * Create Buffer Command.
			 * This command creates a stagging buffer and returns its handle.
			 */
			struct CreateBufferCommand : public CommandBase {
			};

			/**
			 * Submit Data To Buffer Command.
			 * Using this command, data can be submitted to a perticular buffer.
			 */
			struct SubmitDataToBufferCommand : public CommandBase {
			};
		}
	}
}