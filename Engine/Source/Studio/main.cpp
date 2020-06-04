#include "dmkafx.h"
#include "Dynamik.h"
#include "GUI/GUICore/GUICore.h"
#include "GUI/GUIManager/GUIManager.h"
#include "Core/Math/MathFunctions.h"
using namespace Dynamik;

I32 main(I32 argc, CCPTR argv[])
{
    Dynamik::DMKEngine _engine;
    _engine.createInstance(Dynamik::DMKEngineInstanceDescriptor());
	_engine.createWindow();

	_engine.initializeComponents();
	_engine.execute();

	return 0;
}