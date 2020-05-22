/*
 Main entry point for the Dynamik Studio.

 Author:    Dhirak Wishal
 Date:      19/05/2020
*/
#include "studioafx.h"
#include "Dynamik.h"
using namespace Dynamik;

#using "E:\\Projects\\Dynamik Engine\\Versions\\DynamikEngine\\Builds\\Engine\\Binaries\\Debug-x64\\netcoreapp3.1\\Platform.Windows.UI.dll"
using namespace Platform::Windows::UI;

#using <System.dll>
#using <System.Drawing.dll>
#using <PresentationFramework.dll>
#using <PresentationCore.dll>
#using <System.Windows.dll>

using namespace System;

I32 main(I32 argc, CPTR* argv)
{
	DMKEngine::createInstance();
	DMKEngine::execute();

	CustomControl1^ _newControl = gcnew CustomControl1;
	while (true);

	return 0;
}