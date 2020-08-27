// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Ticker.h"

#include <chrono>

void DMKTicker::setTickSize(DMKTickSize tickSize)
{
	this->tickSize = tickSize;
}

DMKTickSize DMKTicker::getTickSize() const
{
	return tickSize;
}

void DMKTicker::start()
{
	startTime = Cast<D64>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

UI64 DMKTicker::getTicks()
{
	return Cast<UI64>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) - Cast<UI64>(startTime);
}

void DMKTicker::end()
{
	startTime = 0.0;
}
