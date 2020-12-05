// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include "GraphicsCore/Objects/BufferHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			/**
			 * Create Stagging Buffer Command.
			 * This command creates a stagging buffer and returns its handle.
			 */
			struct CreateStaggingBufferCommand {
				UI64 mSize = 0;	// The size of the buffer.
			};
		}
	}
}