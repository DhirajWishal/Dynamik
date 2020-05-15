#include "dmkafx.h"
#include "Clock.h"

#include "Error/ErrorManager.h"

#include <chrono>

#define GET_CURRENT_TIME std::chrono::high_resolution_clock::now()
#define GET_MICRO_SECONDS(timePoint) std::chrono::time_point_cast<std::chrono::microseconds>(timePoint).time_since_epoch().count()

namespace Dynamik
{
	DMK_CLASS_SINGLETON_IMPL(DMKClock);

	void DMKClock::start()
	{
		instance.startTime = GET_MICRO_SECONDS(GET_CURRENT_TIME);
	}
	
	void DMKClock::end()
	{
		auto duration = GET_MICRO_SECONDS(GET_CURRENT_TIME) - instance.startTime;

		DMKErrorManager::logDebug(std::to_string(duration / 1000));
	}
	
#if (__cplusplus == 201704L)
	UI64 DMKClock::getCurrentUTC()
	{
		return UI64();
	}
	
	UI64 DMKClock::getCurrentTAI()
	{
		return UI64();
	}
	
	UI64 DMKClock::getCurrentGPS()
	{
		return UI64();
	}
	
	UI64 DMKClock::getCurrentFileTime()
	{
		return UI64();
	}
	
	UI64 DMKClock::getCurrentLocal()
	{
		return UI64();
	}

#endif

	UI64 DMKClock::tick()
	{
		auto _tick = GET_MICRO_SECONDS(GET_CURRENT_TIME) - instance.frameTime;
		frameTime = GET_MICRO_SECONDS(GET_CURRENT_TIME);

		return _tick;
	}
}