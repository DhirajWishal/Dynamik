#include "dmkafx.h"
#include "ThreadManager.h"

#include <thread>

namespace Dynamik
{
	UI32 DMKThreadManager::getUseableThreadCount()
	{
		return std::thread::hardware_concurrency();
	}
}