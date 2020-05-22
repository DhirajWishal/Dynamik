#include "Interface.h"
#include "Dynamik.h"

namespace Dynamik
{
	void DMKStudioInterface::initiate()
	{
		DMKEngine::createInstance();
	}

	void DMKStudioInterface::run()
	{
		DMKEngine::execute();
	}

	void DMKStudioInterface::terminate()
	{
	}
}