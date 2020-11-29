// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendFunction.h"

#include "GraphicsCore/Commands/CoreCommands.h"
#include "GraphicsCore/Commands/RenderTargetCommands.h"

#include "VulkanBackend/Common/VulkanDeviceManager.h"
#include "VulkanBackend/Common/Utilities.h"

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

						auto& mCreateCommand = pCommand->GetData<GraphicsCore::Commands::CreateDevice>();

						// If the device handle pointer is defined, provide data to it. Ignore if false.
						if (mCreateCommand.pDeviceHandle)
							*mCreateCommand.pDeviceHandle = vDeviceManager.CreateDevice(mCreateCommand.initInfo);
						else
							vDeviceManager.CreateDevice(mCreateCommand.initInfo);

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
						auto& mCreateCommand = pCommand->GetData<GraphicsCore::Commands::CreateRenderTarget>();
						auto pDevice = vDeviceManager.GetDeviceAddress(mCreateCommand.mDeviceHandle);

						// Select the best extent which is supported.
						auto bestExtent = Utilities::ChooseSwapExtent(pDevice->GetSurfaceCapabilities(), static_cast<UI32>(mCreateCommand.mExtent.width), static_cast<UI32>(mCreateCommand.mExtent.height));

						// Select the best buffer count which is supported.
						auto vSupport = pDevice->GetSwapChainSupportDetails();
						if (mCreateCommand.bufferCount > vSupport.capabilities.maxImageCount || mCreateCommand.bufferCount < vSupport.capabilities.minImageCount)
						{
							mCreateCommand.bufferCount = static_cast<UI64>(vSupport.capabilities.minImageCount) + 1;
							if (vSupport.capabilities.maxImageCount > 0 && mCreateCommand.bufferCount > vSupport.capabilities.maxImageCount)
								mCreateCommand.bufferCount = vSupport.capabilities.maxImageCount;
						}

						GraphicsCore::RenderTargetHandle mHandleRT = {};

						// Resolve the attachments.
						for (auto itr = mCreateCommand.mAttachments.begin(); itr != mCreateCommand.mAttachments.end(); itr++)
						{
							switch (itr->type)
							{
							case DMK::GraphicsCore::RenderTargetAttachmentType::SWAP_CHAIN:
								// Create the swap chain.
								mHandleRT.attachmentHandles.insert(mHandleRT.attachmentHandles.end(), pDevice->CreateSwapChain(mCreateCommand.bufferCount, *itr, bestExtent));
								break;
							case DMK::GraphicsCore::RenderTargetAttachmentType::COLOR_BUFFER:
								// Create the color buffer.
								mHandleRT.attachmentHandles.insert(mHandleRT.attachmentHandles.end(), pDevice->CreateColorBuffer(mCreateCommand.bufferCount, *itr, bestExtent));
								break;
							case DMK::GraphicsCore::RenderTargetAttachmentType::DEPTH_BUFFER:
								// Create the depth buffer.
								mHandleRT.attachmentHandles.insert(mHandleRT.attachmentHandles.end(), pDevice->CreateDepthBuffer(mCreateCommand.bufferCount, *itr, bestExtent));
								break;
							default:
								Logger::LogError(TEXT("Invalid Render Target Attachment Type!"));
								break;
							}
						}

						// Create the render pass.
						mHandleRT.mRenderPassID = pDevice->CreateRenderPass(mHandleRT.attachmentHandles);

						// Create the frame buffer.
						mHandleRT.mFrameBufferID = pDevice->CreateFrameBuffer(mHandleRT.mRenderPassID, mHandleRT.attachmentHandles, mCreateCommand.bufferCount, bestExtent);

						// Set the handle data if the pointer is valid.
						if (mCreateCommand.pHandle)
							*mCreateCommand.pHandle = mHandleRT;

						SET_COMMAND_SUCCESS(pCommand);
					}

					// Destroy a render target.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::DestroyRenderTarget))
					{
						SET_COMMAND_EXECUTING(pCommand);
						auto& mCreateCommand = pCommand->GetData<GraphicsCore::Commands::DestroyRenderTarget>();

						// Get the required device.
						auto pDevice = vDeviceManager.GetDeviceAddress(mCreateCommand.mDeviceHandle);

						// Destroy all frame buffers.
						pDevice->DestroyFrameBuffer(mCreateCommand.mHandle.mFrameBufferID);

						// Destroy all render passes.
						pDevice->DestroyRenderPass(mCreateCommand.mHandle.mRenderPassID);

						// Terminate the attachments.
						for (auto itr = mCreateCommand.mHandle.attachmentHandles.begin(); itr != mCreateCommand.mHandle.attachmentHandles.end(); itr++)
						{
							switch (itr->mType)
							{
							case DMK::GraphicsCore::RenderTargetAttachmentType::SWAP_CHAIN:
								// Terminate the swap chain.
								pDevice->DestroySwapChain(*itr);
								break;
							case DMK::GraphicsCore::RenderTargetAttachmentType::COLOR_BUFFER:
								// Terminate the color buffer.
								pDevice->DestroyColorBuffer(*itr);
								break;
							case DMK::GraphicsCore::RenderTargetAttachmentType::DEPTH_BUFFER:
								// Terminate the depth buffer.
								pDevice->DestroyDepthBuffer(*itr);
								break;
							default:
								Logger::LogError(TEXT("Invalid Render Target Attachment Type!"));
								break;
							}
						}

						SET_COMMAND_SUCCESS(pCommand);
					}

					// Destroy all render targets.
					else if (pCommand->GetCommandName() == TYPE_NAME(GraphicsCore::Commands::DestroyAllRenderTargets))
					{
						SET_COMMAND_EXECUTING(pCommand);
						auto& mCreateCommand = pCommand->GetData<GraphicsCore::Commands::DestroyAllRenderTargets>();

						// Get the required device.
						auto pDevice = vDeviceManager.GetDeviceAddress(mCreateCommand.mDeviceHandle);

						// Destroy all frame buffers.
						pDevice->DestroyAllFrameBuffers();

						// Destroy all render passes.
						pDevice->DestroyAllRenderPasses();

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