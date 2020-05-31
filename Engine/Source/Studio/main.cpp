#include "dmkafx.h"
#include "Dynamik.h"
#include "GUI/GUICore/GUICore.h"
using namespace Dynamik;

I32 main(I32 argc, CCPTR argv[])
{
	Dynamik::DMKEngine _engine;
	_engine.createInstance(Dynamik::DMKEngineInstanceDescriptor());
	_engine.execute();

	return 0;
}