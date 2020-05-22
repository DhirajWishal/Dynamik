#pragma once
#ifndef _DYNAMIK_STUDIO_INTERFACE_H
#define _DYNAMIK_STUDIO_INTERFACE_H

/*
 Author:    Dhiraj Wishal
 Date:      22/05/2020

 This file contains all the necessary engine components which are exported by the DLL interface.
 The Studio is made in C# which means that we need to have interop support. This project is created to support
 that.
*/

namespace Dynamik
{
	class DMKStudioInterface {
	public:
		DMKStudioInterface() {}
		~DMKStudioInterface() {}

		void initiate();
		void run();
		void terminate();
	};
}

#endif // !_DYNAMIK_STUDIO_INTERFACE_H
