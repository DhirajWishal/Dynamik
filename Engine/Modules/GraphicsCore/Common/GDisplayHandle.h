#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_DISPLAY_HANDLE_H
#define _DYNAMIK_GRAPHICS_CORE_DISPLAY_HANDLE_H

#include "GObject.h"
#include "Inputs/InputCenter.h"

namespace DMK
{
	/**
	 * Graphics Display Create Info.
	 * This structure contains information to create a display object.
	 */
	struct DMK_API GDisplayCreateInfo {
		STRING title = TEXT("Dynamik Engine");
		UI32 width = 1280;
		UI32 height = 720;
	};

	/**
	 * Graphics Display Handle for the Dynamik Engine.
	 * This object holds information about a single display object created by the graphics backend.
	 */
	class DMK_API GDisplayHandle : public GObject {
	public:
		/**
		 * Default constructor.
		 */
		GDisplayHandle() {}

		/**
		 * Default destructor.
		 */
		virtual ~GDisplayHandle() {}

		/**
		 * Initialize the display object.
		 *
		 * @param createInfo: The graphics display create info sturcture.
		 */
		virtual void Initialize(const GDisplayCreateInfo& createInfo) {}

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
		virtual void SetupInputCenter(InputCenter* pInputCenter) {}

		/**
		 * Get the current input center pointer.
		 */
		InputCenter* GetInputCenter() const { return pInputCenter; }

		/**
		 * Poll all the inputs occured in a given time frame.
		 */
		virtual void PollInputs() {}

		/* Data */
	protected:
		GDisplayCreateInfo displayCreateInfo = {};
		InputCenter* pInputCenter = nullptr;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_DISPLAY_HANDLE_H
