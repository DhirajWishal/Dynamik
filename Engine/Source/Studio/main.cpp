#include "dmkafx.h"
#include "Dynamik.h"
#include "GUI/GUICore/GUICore.h"
#include "GUI/GUIManager/GUIManager.h"
#include "Core/Math/MathFunctions.h"
using namespace Dynamik;

I32 main(I32 argc, CCPTR argv[])
{
	DMKEngineInstanceDescriptor _instanceDescriptor;
	DMKGamePackage _package;

	DMKEngine _engine(_instanceDescriptor, &_package);

	_engine.execute();

	return 0;
}