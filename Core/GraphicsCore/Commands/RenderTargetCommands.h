// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/RenderTargetHandle.h"

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
			struct CreateRenderTarget {
				/**
				 * Default constructor.
				 */
				CreateRenderTarget() = default;

				/**
				 * Create the render target using the attachments.
				 *
				 * @param attachments: The attachments defining the render target specification.
				 * @param deviceHandle: The device handle in which the render target is created.
				 * @param pHandle: The Render Target Handle pointer.
				 */
				CreateRenderTarget(const std::vector<RenderTargetAttachmentSpecification>& attachments, const DeviceHandle& deviceHandle, RenderTargetHandle* pHandle = nullptr)
					: mAttachments(attachments), mDeviceHandle(deviceHandle), pHandle(pHandle) {}

				std::vector<RenderTargetAttachmentSpecification> mAttachments;	// RT attachments.
				RenderTargetHandle* pHandle = nullptr;	// Render Target Handle pointer.
				DeviceHandle mDeviceHandle = {};	// Device handle.
			};

			/**
			 * Destroy All Render Targets commands.
			 * This command destroys all the created render targets in the backend in a given device.
			 */
			struct DestroyAllRenderTargets {
				/**
				 * Default constructor.
				 */
				DestroyAllRenderTargets() = default;

				/**
				 * Construct the command using the device handle.
				 *
				 * @param deviceHandle: The device handle to be initialize with.
				 */
				DestroyAllRenderTargets(const DeviceHandle& deviceHandle) : mDeviceHandle(deviceHandle) {}

				DeviceHandle mDeviceHandle = {};	// Device handle.
			};
		}
	}
}