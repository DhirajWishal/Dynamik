#include "dmkafx.h"
#include "SubComponentManager.h"

namespace Dynamik
{
	DMKSubComponentManager::~DMKSubComponentManager()
	{
		for (auto _component : subComponents)
			StaticAllocator<ISubComponentArray>::deallocate(_component.second, 0);
	}
}
