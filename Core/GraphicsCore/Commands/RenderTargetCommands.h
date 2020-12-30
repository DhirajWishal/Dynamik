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
				DeviceHandle mDeviceHandle = {};	// Device handle.
				UI64 bufferCount = 0;	// Number of buffers to be created.
			};

			/**
			 * Destroy Render Target command.
			 * This command terminates a created render pass object.
			 */
			struct DestroyRenderTarget : public CommandBase {
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