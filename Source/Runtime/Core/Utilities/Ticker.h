// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TICKER_H
#define _DYNAMIK_TICKER_H

#include "Core/Types/DataTypes.h"

namespace Dynamik
{
	/* Size of the tick */
	enum class DMK_API DMKTickSize {
		DMK_TICK_SIZE_SECOND,
		DMK_TICK_SIZE_MILLISECOND,
		DMK_TICK_SIZE_MICROSECOND,
		DMK_TICK_SIZE_NANOSECOND
	};

	/*
	 Dynamik Ticker
	 This object keeps count of the number of ticks that took place in a given time.
	*/
	class DMK_API DMKTicker {
	public:
		DMKTicker() {}
		DMKTicker(DMKTickSize tickSize) : tickSize(tickSize) {}
		~DMKTicker() {}

		/*
		 Set the tick size of the ticker.
		*/
		void setTickSize(DMKTickSize tickSize);

		/*
		 Get the tick size of the ticker.
		*/
		DMKTickSize getTickSize() const;

		/*
		 Start the ticker.
		*/
		void start();

		/*
		 Get the number of ticks for the calling instance.
		*/
		UI64 getTicks();

		/*
		 End the ticker.
		*/
		void end();

	private:
		D64 startTime = 0.0;
		DMKTickSize tickSize = DMKTickSize::DMK_TICK_SIZE_MILLISECOND;
	};
}

#endif // !_DYNAMIK_TICKER_H
