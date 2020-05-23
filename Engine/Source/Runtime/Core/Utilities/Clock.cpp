#include "dmkafx.h"
#include "Clock.h"

#include "Error/ErrorManager.h"

#include <chrono>
#include <ctime>   
#include <iomanip>

#define GET_CURRENT_TIME std::chrono::high_resolution_clock::now()
#define GET_MICRO_SECONDS(timePoint) std::chrono::time_point_cast<std::chrono::microseconds>(timePoint).time_since_epoch().count()

namespace Dynamik
{
	void DMKClock::start()
	{
		startTime = GET_MICRO_SECONDS(GET_CURRENT_TIME);
	}

	void DMKClock::end()
	{
		auto duration = GET_MICRO_SECONDS(GET_CURRENT_TIME) - startTime;

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

	Time DMKClock::get()
	{
		Time _time;
		_time.micros = GET_MICRO_SECONDS(GET_CURRENT_TIME) - startTime;
		_time.millis = _time.micros / 1000;
		_time.seconds = _time.millis / 1000;
		_time.minutes = _time.seconds / 60;
		_time.hours = _time.minutes / 60;

		return _time;
	}

	Time DMKClock::getLocal()
	{
		auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		Time _time;
		_time.hours = std::localtime(&in_time_t)->tm_hour;
		_time.minutes = std::localtime(&in_time_t)->tm_min;
		_time.seconds = std::localtime(&in_time_t)->tm_sec;

		return _time;
	}

	UI64 DMKClock::tick()
	{
		auto _tick = GET_MICRO_SECONDS(GET_CURRENT_TIME) - frameTime;
		frameTime = GET_MICRO_SECONDS(GET_CURRENT_TIME);

		return _tick;
	}
}