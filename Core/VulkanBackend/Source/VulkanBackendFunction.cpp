// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendFunction.h"

#include "GraphicsCore/Commands/CoreCommands.h"
#include "VulkanBackend/Common/VulkanDeviceManager.h"

#define TYPE_NAME(type)	typeid(type).name()
#define DELETE(type)	delete pCommand->Derived<type>(), pCommand = nullptr

#define SET_COMMAND_STATE_PENDING(command)		command->SetState(Threads::CommandState::COMMAND_STATE_PENDING)
#define SET_COMMAND_STATE_EXECUTING(command)	command->SetState(Threads::CommandState::COMMAND_STATE_EXECUTING)
#define SET_COMMAND_STATE_SUCCESS(command)		command->SetState(Threads::CommandState::COMMAND_STATE_SUCCESS)
#define SET_COMMAND_STATE_FAILED(command)		command->SetState(Threads::CommandState::COMMAND_STATE_FAILED)

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanBackendFunction(Threads::CommandQueue<THREAD_MAX_COMMAND_COUNT>* pCommandQueue)
		{
			// Setup the Vulkan Instance.
			VulkanInstance vInstance = {};

			// Setup the Vulkan Device Manager.
			VulkanDeviceManager vDeviceManager = {};

			// State of the main loop.
			bool ShouldRun = true;

			// Iterate through the commands and execute them.
			do
			{
				// Check if commands are available.
				if (pCommandQueue->Count())
				{
					// Get the first command.
					auto pCommand = pCommandQueue->GetAndPop();
					SET_COMMAND_STATE_PENDING(pCommand);

					// Initialize backend (Vulkan Instance) command.
					if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::InitializeBackend))
					{
						SET_COMMAND_STATE_EXECUTING(pCommand);

						// Initialize the instance.
						vInstance.Initialize(pCommand->Derived<GraphicsCore::Commands::InitializeBackend>()->Get().enableValidation);

						// Initialize the device manager.
						vDeviceManager.Initialize(&vInstance);

						SET_COMMAND_STATE_SUCCESS(pCommand);

						// Delete the command.
						DELETE(GraphicsCore::Commands::InitializeBackend);
					}

					// Terminate the backend.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::TerminateBackend))
					{
						// Terminate the device manager.
						vDeviceManager.Terminate();

						// Terminate the instance.
						vInstance.Terminate();

						// Set the run state to false.
						ShouldRun = false;

						// Delete the command.
						DELETE(GraphicsCore::Commands::TerminateBackend);
					}

					// Create a new device command.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::CreateDevice))
					{
						auto pCreateCommand = pCommand->Derived<GraphicsCore::Commands::CreateDevice>();

						// If the device handle pointer is defined, provide data to it. Ignore if false.
						if (pCreateCommand->Get().pDeviceHandle)
							*pCreateCommand->Get().pDeviceHandle = vDeviceManager.CreateDevice(pCreateCommand->Get().initInfo);
						else
							vDeviceManager.CreateDevice(pCreateCommand->Get().initInfo);

						// Delete the command.
						DELETE(GraphicsCore::Commands::CreateDevice);
					}

					// Destroy a created device.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::DestroyDevice))
					{
						// Destroy the device.
						vDeviceManager.DestroyDevice(pCommand->Derived<GraphicsCore::Commands::DestroyDevice>()->Get().mDeviceHandle);

						// Delete the command.
						DELETE(GraphicsCore::Commands::DestroyDevice);
					}

					// If execution failed.
					if (pCommand)
					{
						SET_COMMAND_STATE_FAILED(pCommand);

						// Delete the command.
						delete pCommand;
					}
				}

				// Poll inputs.
				vDeviceManager.PollInputs();
			} while (ShouldRun);
		}
	}
}