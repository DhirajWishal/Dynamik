#include "dmkafx.h"
#include "RendererThread.h"

namespace Dynamik
{
	void DMKRendererThread::processCommands()
	{
		for (auto _command : myCommands)
		{
			myCommand = (DMKRendererThreadCommand*)_command;

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
			default:
				break;
			}
		}

		myCommands.clear();
	}
	
	void DMKRendererThread::onLoop()
	{
		myRenderer.initializeDraw();

		processCommands();

		myRenderer.updateObjects();
		myRenderer.submitObjects();
	}
	
	void DMKRendererThread::onTermination()
	{
	}
}
