// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			/**
			 * Command Type enum.
			 */
			enum class CommandType : UI32 {
				UNDEFINED,
				INITIALIZE_BACKEND,
				TERMINATE_BACKEND,
				CREATE_DEVICE,
				DESTROY_DEVICE,

				CREATE_RENDER_TARGET,
				DESTROY_RENDER_TARGET,
				DESTROY_ALL_RENDER_TARGETS,

				CREATE_BUFFER,
				SUBMIT_DATA_TO_BUFFER,
				DESTROY_BUFFER,
				DESTROY_ALL_BUFFERS,
			};

			/**
			 * The command base structure.
			 * This is the base structure for all the graphics commands.
			 */
			struct CommandBase {
				/**
				 * Default constructor.
				 * Construct the command base using the command type.
				 *
				 * @param type: The command type.
				 */
				CommandBase(CommandType type) : mCommandType(type) {}
				~CommandBase() = default;

				CommandType mCommandType = CommandType::UNDEFINED;	// Command type.
			};
		}
	}
}