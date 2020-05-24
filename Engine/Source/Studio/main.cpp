#include "dmkafx.h"
#include "GUI/GUICore/GUICore.h"
using namespace Dynamik;

I32 main(I32 argc, CCPTR argv[])
{
	try
	{
		GUICore _core;
		_core.initialize();
		while (true)
		{
			_core.initializeFrame();
			_core.updateRenderables();
			_core.submitRenderables();
		}
	}
	catch (const std::exception&)
	{
		return -1;
	}

	return 0;
}