// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H
#define _DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H

#include "GraphicsCore/Common/DisplayHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Display Handle for the Dynamik Engine.
			 */
			class DMK_API VulkanDisplayHandle : public DisplayHandle {
			public:
				/**
				 * Default constructor.
				 */
				VulkanDisplayHandle() {}

				/**
				 * Default destructor.
				 */
				~VulkanDisplayHandle() {}

				/**
				 * Initialize the display object.
				 *
				 * @param createInfo: The graphics display create info sturcture.
				 */
				virtual void Initialize(const DisplayCreateInfo& createInfo) override final;

				/**
				 * Set an icon to the display.
				 *
				 * @param file: The image path.
				 */
				virtual void SetIcon(const STRING& file)  override final;

				/**
				 * Terminate the display object.
				 */
				virtual void Terminate()  override final;

				/**
				 * Setup the input center of the current display object.
				 */
				virtual void SetupInputCenter()  override final;

				/**
				 * Poll all the inputs occured in a given time frame.
				 */
				virtual void PollInputs()  override final;

				/**
				 * Resize the window object.
				 *
				 * @param extent: The new window extent.
				 */
				virtual void Resize(const DisplayExtent& extent) override final;

				/* Data */
			private:
				void* pWindowHandle = nullptr;
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H
