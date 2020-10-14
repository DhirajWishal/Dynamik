// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_DISPLAY_HANDLE_H
#define _DYNAMIK_GRAPHICS_CORE_DISPLAY_HANDLE_H

#include "Object.h"
#include "Inputs/InputCenter.h"
#include "Core/Types/Utilities.h"
#include "Core/Math/Vector/Vector2F.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Structure containing the display extent.
		 */
		struct DMK_API DisplayExtent {
			/**
			 * Default constructor.
			 *
			 * @param width: The width. Default is 0;
			 * @param height: The height. Default is 0;
			 */
			DisplayExtent(UI32 width = 0, UI32 height = 0) : width(width), height(height) {}

			UI32 width = 0;
			UI32 height = 0;
		};

		/**
		 * Graphics Display Create Info.
		 * This structure contains information to create a display object.
		 */
		struct DMK_API DisplayCreateInfo {
			STRING title = TEXT("Dynamik Engine");
			DisplayExtent extent = { 1280U, 720U };
		};

		/**
		 * Graphics Display Handle for the Dynamik Engine.
		 * This object holds information about a single display object created by the graphics backend.
		 *
		 * Each display handle contains an input center.
		 */
		class DMK_API DisplayHandle : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			DisplayHandle() {}

			/**
			 * Default destructor.
			 */
			virtual ~DisplayHandle() {}

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

			/**
			 * Get the current extent of the window.
			 */
			DisplayExtent GetExtent() const { return createInfo.extent; }

			/**
			 * Resize the window object.
			 *
			 * @param extent: The new window extent.
			 */
			virtual void Resize(const DisplayExtent& extent) {}

			/* Data */
		protected:
			DisplayCreateInfo createInfo = {};
			Inputs::InputCenter inputCenter = {};

		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_DISPLAY_HANDLE_H
