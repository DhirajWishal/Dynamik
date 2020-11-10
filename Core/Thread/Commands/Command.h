// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_COMMAND_H
#define _DYNAMIK_THREAD_COMMAND_H

#include "Core/Types/DataTypes.h"
#include "Core/Macros/Global.h"

#include <mutex>

namespace DMK
{
	std::mutex __GlobalThreadCommandMutex = {};

	namespace Threads
	{
		/**
		 * Base bject for the commands.
		 */
		class CommandBase {
		public:
			/**
			 * Default constructor.
			 */
			CommandBase() {}

			/**
			 * Default destructor.
			 */
			virtual ~CommandBase() {}
		};

		/**
		 * Thread command object.
		 * This object is used to store a single type of commands a thread can handle.
		 */
		template<class Type>
		class Command : public CommandBase {
		public:
			/**
			 * Default constructor.
			 */
			Command() {}

			/**
			 * Default destructor.
			 */
			~Command() {}

			/**
			 * Set command data (copy).
			 *
			 * @param data: The data to be set.
			 */
			DMK_FORCEINLINE void Set(const Type& data) { mData = data; }

			/**
			 * Set command data (move).
			 *
			 * @param data: The data to be set.
			 */
			DMK_FORCEINLINE void Set(Type&& data) { mData = std::move(data); }

			/**
			 * Get data from the command.
			 *
			 * @return const Type.
			 */
			DMK_FORCEINLINE const Type Get() const { return mData; }

			/**
			 * Get data from the command.
			 *
			 * @return Type reference.
			 */
			DMK_FORCEINLINE Type& Get() { return mData; }

		private:
			Type mData = Type();	// Stored data.
		};
	}
}

#endif // !_DYNAMIK_THREAD_COMMAND_H
