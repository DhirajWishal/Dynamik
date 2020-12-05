// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

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
			 * Construct the view port using the device which it was created with.
			 *
			 * @param pDevice: The device which created it.
			 */
			ViewPort(class GDevice* pDevice) : pDevice(pDevice) {}

			/**
			 * Set the device of the view port.
			 *
			 * @param pDevice: The device which created the view port.
			 */
			DMK_FORCEINLINE void SetDevice(class GDevice* pDevice) { this->pDevice = pDevice; }

			/**
			 * Get the device of the view port.
			 *
			 * @return GDevice class pointer.
			 */
			DMK_FORCEINLINE class GDevice* GetDevice() const { this->pDevice; }

			/**
			 * Set the offsets of the view port.
			 * Offsets are calculated from the top left corner of the window/ display in window coordinates.
			 *
			 * @param xOffset: The xOffset of the view port.
			 * @param yOffset: The yOffset of the view port.
			 */
			DMK_FORCEINLINE void SetOffsets(float xOffset, float yOffset) { this->xOffset = xOffset, this->yOffset = yOffset; }

			/**
			 * Get the offsets of the view port.
			 *
			 * @return std::pair<float, float> containing the xOffset and yOffset.
			 */
			DMK_FORCEINLINE std::pair<float, float> GetOffsets() const { return { xOffset, yOffset }; }

			/**
			 * Set the size of the viewport.
			 *
			 * @param width: The width of the viewport.
			 * @param height: The height of the viewport.
			 */
			DMK_FORCEINLINE void SetSize(UI32 width, UI32 height) { this->width = width, this->height = height; }

			/**
			 * Get the width and height of the view port.
			 *
			 * @return std::pair<UI32, UI32> containing the width and height.
			 */
			DMK_FORCEINLINE std::pair<UI32, UI32> GetSize() { return { width, height }; }

			class GDevice* pDevice = nullptr;	// The device which created the viewport.

			float xOffset = 0.0f, yOffset = 0.0f;	// Offsets of the view port in the window space.
			UI32 width = 0, height = 0;	// Width and Height of the view port.
		};
	}
}
