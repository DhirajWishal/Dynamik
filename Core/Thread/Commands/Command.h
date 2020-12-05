// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include "Core/Macros/Global.h"

#include <mutex>

namespace DMK
{
	namespace Thread
	{
		template<class Type> class Command;

		/**
		 * Command State enum.
		 * This defines the states of a given command.
		 */
		enum class CommandState : UI8 {
			PENDING,		// Command is waiting in the queue.
			EXECUTING,	// Command is being executed.
			SUCCESS,		// Command execution was successful.
			FAILED,		// Command execution failed.
			INVALID		// Invalid command was passed.
		};

		/**
		 * Base bject for the commands.
		 */
		class CommandBase {
		public:
			CommandBase(CommandState* pCommandState = nullptr) : pComandState(pCommandState) {}
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
			 * Get the data stored in the command.
			 *
			 * @tparam Type: The type of the command.
			 * @return The command type.
			 */
			template<class Type>
			constexpr Type& GetData() { return Derived<Type>()->Get(); }

			/**
			 * Get the data stored in the command.
			 *
			 * @tparam Type: The type of the command.
			 * @return The command type.
			 */
			template<class Type>
			constexpr const Type GetData() const { return Derived<Type>()->Get(); }

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
