#pragma once
#ifndef _DYNAMIK_STUDIO_CALL_BRIDGE_H
#define _DYNAMIK_STUDIO_CALL_BRIDGE_H

#include "Interface.h"

extern "C" {
	extern _declspec(dllexport) Dynamik::DMKStudioInterface* createInterface();
	extern _declspec(dllexport) void initialize(Dynamik::DMKStudioInterface* intrf);
	extern _declspec(dllexport) void execute(Dynamik::DMKStudioInterface* intrf);
	extern _declspec(dllexport) void terminate(Dynamik::DMKStudioInterface* intrf);
}

#endif // !_DYNAMIK_STUDIO_CALL_BRIDGE_H
