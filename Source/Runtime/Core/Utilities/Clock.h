// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CLOCK_H
#define _DYNAMIK_CLOCK_H

/*
 Clock class for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

namespace Dynamik
{
	/* Container to store time */
	struct DMK_API Time {
		D64 hours = 0;
		D64 minutes = 0;
		D64 seconds = 0;
		D64 millis = 0;
		D64 micros = 0;
	};

	/*
	 Benchmark
	*/
	struct DMK_API Benchmark {

	};

	/*
	 This class contains all the time functions required by the Dynamik Engine.
	*/
	class DMK_API DMKClock {
	public:
		DMKClock() {}
		~DMKClock() {}

		/*
		 Start the clock. Users are not reuired to start the clock explicitly because it is
		 automatically started by the engine.
		*/
		void start();

		/*
		 End the clock. Calling this while running the engine will cause a runtime error.
		 The engine automatically calls this function upon termination.
		*/
		void end();

#if (__cplusplus == 201704L)    /* These features are only available in C++ 20 */
		UI64 getCurrentUTC();
		UI64 getCurrentTAI();
		UI64 getCurrentGPS();
		UI64 getCurrentFileTime();
		UI64 getCurrentLocal();

#endif

		/* Get the current time since engine initiation */
		Time get();

		/* Get the local time */
		Time getLocal();

		/* This functions returns a tick for each main loop iteration */
		UI64 tick();

	private:
		UI64 startTime = 0; /* start time in micro seconds */
		UI64 frameTime = 0; /* Calculates tick */
	};
}

#endif // !_DYNAMIK_CLOCK_H