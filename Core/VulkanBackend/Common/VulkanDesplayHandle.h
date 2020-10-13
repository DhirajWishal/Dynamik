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
			class DMK_API VulkanDesplayHandle : public DisplayHandle {
			public:
				/**
				 * Default constructor.
				 */
				VulkanDesplayHandle() {}

				/**
				 * Default destructor.
				 */
				~VulkanDesplayHandle() {}

				/**
				 * Initialize the display object.
				 *
				 * @param createInfo: The graphics display create info sturcture.
				 */
				virtual void Initialize(const DisplayCreateInfo& createInfo) {}

				/**
				 * Set an icon to the display.
				 *
				 * @param file: The image path.
				 */
				virtual void SetIcon(const STRING& file) {}

				/**
				 * Terminate the display object.
				 */
				virtual void Terminate() {}

				/**
				 * Setup the input center of the current display object.
				 */
				virtual void SetupInputCenter() {}

				/**
				 * Get the current input center pointer.
				 */
				Inputs::InputCenter* GetInputCenter() const { return Cast<Inputs::InputCenter*>(&inputCenter); }

				/**
				 * Poll all the inputs occured in a given time frame.
				 */
				virtual void PollInputs() {}
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H
