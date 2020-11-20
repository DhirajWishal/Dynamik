// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include "Core/Macros/Global.h"

#include <mutex>

namespace DMK
{
	namespace Threads
	{
		template<class Type> class Command;

		/**
		 * Command State enum.
		 * This defines the states of a given command.
		 */
		enum class CommandState : UI8 {
			COMMAND_STATE_PENDING,		// Command is waiting in the queue.
			COMMAND_STATE_EXECUTING,	// Command is being executed.
			COMMAND_STATE_SUCCESS,		// Command execution was successful.
			COMMAND_STATE_FAILED,		// Command execution failed.
			COMMAND_STATE_INVALID		// Invalid command was passed.
		};

		/**
		 * Base bject for the commands.
		 */
		class CommandBase {
		public:
			/**
			 * Default constructor.
			 */
			CommandBase(CommandState* pCommandState = nullptr) : pComandState(pCommandState) {}

			/**
			 * Default destructor.
			 */
			virtual ~CommandBase() {}

			/**
			 * Get the command type name.
			 *
			 * @return Const char pointer name.
			 */
			virtual const char* GetCommandName() const { return nullptr; }

			/**
			 * Cast and get the command as the derived type.
			 *
			 * @tparam Type: The type of the command.
			 * @return The Command<Type> pointer.
			 */
			template<class Type>
			constexpr Command<Type>* Derived() { return dynamic_cast<Command<Type>*>(this); }

			/**
			 * Set the command state if the command state is valid.
			 *
			 * @param state: The state of the command.
			 */
			void SetState(CommandState state) { if (pComandState) *pComandState = state; }

			CommandState* pComandState = nullptr;	// Command state pointer.
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
			 * This can be used to set the command state pointer.
			 *
			 * @param pCommandState: The command state pointer. Default is nullptr.
			 */
			Command(CommandState* pCommandState = nullptr) : CommandBase(pCommandState) {}

			/**
			 * Construct the command by providing the command data (copy).
			 *
			 * @param command: The command data to initialize with..
			 * @param pCommandState: The command state pointer. Default is nullptr.
			 */
			Command(const Type& command, CommandState* pCommandState = nullptr)
				: mData(command), CommandBase(pCommandState) {}

			/**
			 * Construct the command by providing the command data (move).
			 *
			 * @param command: The command data to initialize with.
			 * @param pCommandState: The command state pointer. Default is nullptr.
			 */
			Command(Type&& command, CommandState* pCommandState = nullptr)
				: mData(std::move(command)), CommandBase(pCommandState) {}

			/**
			 * Default destructor.
			 */
			~Command() {}

			typedef typename Type Type;	// The type of the command.

			/**
			 * Get the command type name.
			 *
			 * @return Const char pointer name.
			 */
			virtual const char* GetCommandName() const override final { return typeid(Type).name(); }

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

		public:
			/**
			 * Get the data pointer.
			 *
			 * @return The address of the stored data.
			 */
			Type* operator->() { return &mData; }

			/**
			 * Get the data pointer.
			 *
			 * @return The address of the stored data.
			 */
			const Type* operator->() const { return &mData; }

		private:
			Type mData = Type();	// Stored data.
		};
	}
}
