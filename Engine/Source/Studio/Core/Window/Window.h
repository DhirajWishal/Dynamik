#pragma once
#ifndef _DYNAMIK_STUDIO_WINDOW_H
#define _DYNAMIK_STUDIO_WINDOW_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "Types/DataTypes.h"

namespace Dynamik
{
	/*
	 Dynamik Studio Window base class.
	*/
	class DMKWindow {
	public:
		DMKWindow() {}
		DMKWindow(const STRING& title, const I32& width, const I32& height)
			: windowTitle(title), windowWidth(width), windowHeight(height) {}
		virtual ~DMKWindow() {}

		virtual void setWindowIcon(const STRING& icon) { windowIconPath = icon; }

		virtual void initialize() {}
		virtual void terminate() {}

		STRING windowTitle = DMK_TEXT("");
		STRING windowIconPath = DMK_TEXT("");
		I32 windowWidth = 0;
		I32 windowHeight = 0;
	};
}

#endif // !_DYNAMIK_STUDIO_WINDOW_H
