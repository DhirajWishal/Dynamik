#include "dmkafx.h"
#include "Dynamik.h"
#include "GUI/GUICore/GUICore.h"
#include "Core/Math/MathFunctions.h"
using namespace Dynamik;

I32 main(I32 argc, CCPTR argv[])
{
	for (UI32 i = 0; i < 100; i++)
	{
		auto lookAt = DMKMathFunctions::lookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
		auto perspec = DMKMathFunctions::perspective(DMKMathFunctions::radians(60.0f), 0.5f, 0.01f, 100.f);
		auto rotate = DMKMathFunctions::rotate(Matrix4F(1.0f), 45.0f, { 0.0f, 1.0f, 0.0f });
	}

	Dynamik::DMKEngine _engine;
	_engine.createInstance(Dynamik::DMKEngineInstanceDescriptor());
	_engine.execute();

	return 0;
}