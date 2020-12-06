// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CommandBase.h"
#include "GraphicsCore/Backend/RenderTargetHandle.h"
#include "GraphicsCore/Backend/DeviceHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			/**
			 * Create Render Target command.
			 * Render target defines where to store the rendering frames and how to display them.
			 *
			 * For 2D rendering context;
			 * - Swap Chain, Color Buffer.
			 *
			 * For 3D rendering context;
			 * - Swap Chain, Depth Buffer, Color Buffer.
			 */
			struct CreateRenderTarget : public CommandBase {
				CreateRenderTarget() : CommandBase(CommandType::CREATE_RENDER_TARGET) {}

				/**
				 * Create the render target using the attachments.
				 *
				 * @param bufferCount: The number of buffers to be created. If the count is 0 or more than what is capable,
				 * the maximum capable buffer count will be set.
				 * @param mExtent: The extent of the render target. If the extent is not supported, the maximum supported will be set.
				 * @param attachments: The attachments defining the render target specification.
				 * @param deviceHandle: The device handle in which the render target is created.
				 * @param pHandle: The Render Target Handle pointer.
				 */
				CreateRenderTarget(UI64 bufferCount, const Vector3& mExtent, const std::vector<RenderTargetAttachmentSpecification>& attachments, const DeviceHandle& deviceHandle, RenderTargetHandle* pHandle = nullptr)
					: CommandBase(CommandType::CREATE_RENDER_TARGET), bufferCount(bufferCount), mExtent(mExtent), mAttachments(attachments), mDeviceHandle(deviceHandle), pHandle(pHandle) {}

				std::vector<RenderTargetAttachmentSpecification> mAttachments;	// RT attachments.
				Vector3 mExtent = Vector3::ZeroAll;	// Extent of the attachment in the frame buffer.
				RenderTargetHandle* pHandle = nullptr;	// Render Target Handle pointer.
				DeviceHandle mDeviceHandle = {};	// Device handle.
				UI64 bufferCount = 0;	// Number of buffers to be created.
			};

			/**
			 * Destroy Render Target command.
			 * This command terminates a created render pass object.
			 */
			struct DestroyRenderTarget : public CommandBase {
				/**
				 * Construct the command using the render target handle and the device handle.
				 *
				 * @param mHandle: The render target handle.
				 * @param mDeviceHandle: The device handle in which the render target was created.
				 */
				DestroyRenderTarget(const RenderTargetHandle& mHandle, const DeviceHandle& mDeviceHandle)
					: CommandBase(CommandType::DESTROY_RENDER_TARGET), mHandle(mHandle), mDeviceHandle(mDeviceHandle) {}

				RenderTargetHandle mHandle = {};	// The render target handle.
				DeviceHandle mDeviceHandle = {};	// The device handle of the render target.
			};

			/**
			 * Destroy All Render Targets command.
			 * This command destroys all the created render targets in the backend in a given device.
			 */
			struct DestroyAllRenderTargets : public CommandBase {
				DestroyAllRenderTargets() : CommandBase(CommandType::DESTROY_ALL_RENDER_TARGETS) {}

				/**
				 * Construct the command using the device handle.
				 *
				 * @param deviceHandle: The device handle to be initialize with.
				 */
				DestroyAllRenderTargets(const DeviceHandle& deviceHandle)
					: CommandBase(CommandType::DESTROY_ALL_RENDER_TARGETS), mDeviceHandle(deviceHandle) {}

				DeviceHandle mDeviceHandle = {};	// Device handle.
			};
		}
	}
}