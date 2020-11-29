// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendFunction.h"

#include "GraphicsCore/Commands/CoreCommands.h"
#include "GraphicsCore/Commands/RenderTargetCommands.h"

#include "VulkanBackend/Common/VulkanDeviceManager.h"

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
			bool bShouldRun = true;

			// Iterate through the commands and execute them.
			do
			{
				// Check if commands are available.
				if (pCommandQueue->Count())
				{
					// Get the first command.
					auto pCommand = pCommandQueue->GetAndPop();
					SET_COMMAND_PENDING(pCommand);

					// Initialize backend (Vulkan Instance) command.
					if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::InitializeBackend))
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Initialize the instance.
						vInstance.Initialize(pCommand->GetData<GraphicsCore::Commands::InitializeBackend>().enableValidation);

						// Initialize the device manager.
						vDeviceManager.Initialize(&vInstance);

						SET_COMMAND_SUCCESS(pCommand);

						// Delete the command.
						DELETE_COMMAND(pCommand, GraphicsCore::Commands::InitializeBackend);
					}

					// Terminate the backend.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::TerminateBackend))
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Terminate the device manager.
						vDeviceManager.Terminate();

						// Terminate the instance.
						vInstance.Terminate();

						// Set the run state to false.
						bShouldRun = false;

						SET_COMMAND_SUCCESS(pCommand);

						// Delete the command.
						DELETE_COMMAND(pCommand, GraphicsCore::Commands::TerminateBackend);
					}

					// Create a new device command.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::CreateDevice))
					{
						SET_COMMAND_EXECUTING(pCommand);

						auto& pCreateCommand = pCommand->GetData<GraphicsCore::Commands::CreateDevice>();

						// If the device handle pointer is defined, provide data to it. Ignore if false.
						if (pCreateCommand.pDeviceHandle)
							*pCreateCommand.pDeviceHandle = vDeviceManager.CreateDevice(pCreateCommand.initInfo);
						else
							vDeviceManager.CreateDevice(pCreateCommand.initInfo);

						SET_COMMAND_SUCCESS(pCommand);

						// Delete the command.
						DELETE_COMMAND(pCommand, GraphicsCore::Commands::CreateDevice);
					}

					// Destroy a created device.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::DestroyDevice))
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Destroy the device.
						vDeviceManager.DestroyDevice(pCommand->GetData<GraphicsCore::Commands::DestroyDevice>().mDeviceHandle);

						SET_COMMAND_SUCCESS(pCommand);

						// Delete the command.
						DELETE_COMMAND(pCommand, GraphicsCore::Commands::DestroyDevice);
					}

					// Create a render target.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::CreateRenderTarget))
					{
						SET_COMMAND_EXECUTING(pCommand);
						auto& pCreateCommand = pCommand->GetData<GraphicsCore::Commands::CreateRenderTarget>();
						auto pDevice = vDeviceManager.GetDeviceAddress(pCreateCommand.mDeviceHandle);

						GraphicsCore::RenderTargetHandle mHandleRT = {};

						// Resolve the attachments.
						for (auto itr = pCreateCommand.mAttachments.begin(); itr != pCreateCommand.mAttachments.end(); itr++)
						{
							switch (itr->type)
							{
							case DMK::GraphicsCore::RenderTargetAttachmentType::SWAP_CHAIN:
								// Create the swap chain.
								mHandleRT.attachmentHandles.insert(mHandleRT.attachmentHandles.end(), pDevice->CreateSwapChain(*itr));
								break;
							case DMK::GraphicsCore::RenderTargetAttachmentType::COLOR_BUFFER:
								// Create the color buffer.
								mHandleRT.attachmentHandles.insert(mHandleRT.attachmentHandles.end(), pDevice->CreateColorBuffer(*itr));
								break;
							case DMK::GraphicsCore::RenderTargetAttachmentType::DEPTH_BUFFER:
								// Create the depth buffer.
								mHandleRT.attachmentHandles.insert(mHandleRT.attachmentHandles.end(), pDevice->CreateDepthBuffer(*itr));
								break;
							default:
								Logger::LogError(TEXT("Invalid Render Target Attachment Type!"));
								break;
							}
						}

						// Set the handle data if the pointer is valid.
						if (pCreateCommand.pHandle)
							*pCreateCommand.pHandle = mHandleRT;

						SET_COMMAND_SUCCESS(pCommand);
					}

					// Destroy all render targets.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::DestroyAllRenderTargets))
					{
						SET_COMMAND_EXECUTING(pCommand);
						auto& pCreateCommand = pCommand->GetData<GraphicsCore::Commands::DestroyAllRenderTargets>();

						// Get the required device.
						auto pDevice = vDeviceManager.GetDeviceAddress(pCreateCommand.mDeviceHandle);

						// Destroy all swap chains.
						pDevice->DestroyAllSwapChains();

						// Destroy all color buffers.
						pDevice->DestroyAllColorBuffers();

						// Destroy all depth buffers.
						pDevice->DestroyAllDepthBuffers();

						SET_COMMAND_SUCCESS(pCommand);
					}

					// If execution failed.
					if (pCommand)
					{
						SET_COMMAND_FAILED(pCommand);

						// Delete the command.
						delete pCommand;
					}
				}

				// Poll inputs.
				vDeviceManager.PollInputs();
			} while (bShouldRun);
		}
	}
}