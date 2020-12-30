// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "BackendHandles.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * View Port object for the Device.
		 * This object contains information about the view port which is created by a device.
		 */
		struct ViewPort {
			ViewPort() = default;

			/**
			 * Construct the view port using the device handle, size and offsets.
			 *
			 * @param deviceHandle: The device handle which created it.
			 * @param width: The width of the view port.
			 * @param height: The height of the view port.
			 * @param xOffset: The X offset of the view port.
			 * @param yOffset: The Y offset of the view port.
			 */
			ViewPort(const DeviceHandle& deviceHandle, UI32 width = 0, UI32 height = 0, float xOffset = 0.0f, float yOffset = 0.0f)
				: mDeviceHandle(deviceHandle), mWidth(width), mHeight(height), mXOffset(xOffset), mYOffset(yOffset) {}

			/**
			 * Set the device handle of the view port.
			 *
			 * @param deviceHandle: The device handle which created the view port.
			 */
			void SetDeviceHandle(const DeviceHandle& deviceHandle) { this->mDeviceHandle = deviceHandle; }

			/**
			 * Get the device handle of the view port.
			 *
			 * @return DeviceHandle handle.
			 */
			DeviceHandle GetDevice() const { this->mDeviceHandle; }

			/**
			 * Set the offsets of the view port.
			 * Offsets are calculated from the top left corner of the window/ display in window coordinates.
			 *
			 * @param xOffset: The xOffset of the view port.
			 * @param yOffset: The yOffset of the view port.
			 */
			void SetOffsets(float xOffset, float yOffset) { this->mXOffset = xOffset, this->mYOffset = yOffset; }

			/**
			 * Get the offsets of the view port.
			 *
			 * @return std::pair<float, float> containing the xOffset and yOffset.
			 */
			std::pair<float, float> GetOffsets() const { return { mXOffset, mYOffset }; }

			/**
			 * Set the size of the viewport.
			 *
			 * @param width: The width of the viewport.
			 * @param height: The height of the viewport.
			 */
			void SetSize(UI32 width, UI32 height) { this->mWidth = width, this->mHeight = height; }

			/**
			 * Get the width and height of the view port.
			 *
			 * @return std::pair<UI32, UI32> containing the width and height.
			 */
			std::pair<UI32, UI32> GetSize() { return { mWidth, mHeight }; }

		public:
			bool operator==(const ViewPort& viewPort) const
			{
				return mDeviceHandle == viewPort.mDeviceHandle
					&& mXOffset == viewPort.mXOffset
					&& mYOffset == viewPort.mYOffset
					&& mWidth == viewPort.mWidth
					&& mHeight == viewPort.mHeight;
			}

		public:
			float mXOffset = 0.0f, mYOffset = 0.0f;	// Offsets of the view port in the window space.
			UI32 mWidth = 0, mHeight = 0;	// Width and Height of the view port.
			DeviceHandle mDeviceHandle = 0;	// The device the view port is created on.
		};
	}
}
