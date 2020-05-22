#include "CallBridge.h"

extern "C" {
	Dynamik::DMKStudioInterface* createInterface()
	{
		return new Dynamik::DMKStudioInterface;
	}

	void initialize(Dynamik::DMKStudioInterface* intrf)
	{
		intrf->initiate();
	}

	void execute(Dynamik::DMKStudioInterface* intrf)
	{
		intrf->run();
	}

	void terminate(Dynamik::DMKStudioInterface* intrf)
	{
		intrf->terminate();
	}
}
