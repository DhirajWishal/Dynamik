#include "dmkafx.h"
#include "RendererThread.h"

namespace Dynamik
{
	void DMKRendererThread::initialize()
	{
		//myRenderer.setMsaaSamples(DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT);
		//myRenderer.initialize();
		DMK_INFO("Entered the renderer thread!");
	}

	void DMKRendererThread::processCommand(POINTER<DMKThreadCommand> command)
	{
		myCommand = (DMKRendererThreadCommand*)command;

		switch (myCommand->instruction)
		{
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE:
			myRenderer.initialize();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SUBMIT_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_INITIALIZE:
			myRenderer.initializeDraw();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE:
			myRenderer.updateObjects();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_SUBMIT:
			myRenderer.submitObjects();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_FRAME:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_UPDATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_UPDATE_SET_SAMPLES:
			myRenderer.setMsaaSamples(*(DMKSampleCount*)myCommand->data);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_UPDATE_SET_WINDOW_HANDLE:
			myRenderer.setWindowHandle((POINTER<DMKWindowHandle>)myCommand->data);
			break;
		default:
			break;
		}
	}

	void DMKRendererThread::onLoop()
	{
		myRenderer.initializeDraw();
		myRenderer.updateObjects();
		myRenderer.submitObjects();
	}

	void DMKRendererThread::onTermination()
	{
		myRenderer.terminate();
		DMK_INFO("Terminated the renderer thread!");
	}
}
