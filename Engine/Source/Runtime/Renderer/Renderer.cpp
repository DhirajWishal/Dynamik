#include "dmkafx.h"
#include "Renderer.h"

namespace Dynamik
{
	void DMKRenderer::initialize()
	{
		//myRenderer.setMsaaSamples(DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT);
		//myRenderer.initialize();
		DMK_INFO("Entered the renderer thread!");
	}

	void DMKRenderer::processCommand(POINTER<DMKThreadCommand> command)
	{
		myCommand = (DMKRendererCommand*)command;

		switch (myCommand->instruction)
		{
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE:
			myBackend.initializeCore();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_CREATE_CONTEXT:
			myBackend.initializeRenderingContext(((RendererCreateContextCommand*)myCommand)->contextType, ((RendererCreateContextCommand*)myCommand)->viewport);
		break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_FINALS:
			myBackend.initializeFinalComponents();
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITY:
			myBackend.initializeEntity(DMKComponentArray<DMKMeshComponent>());
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITIES:
			myBackend.initializeEntities(((RendererAddMeshComponents*)myCommand)->meshComponents);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SUBMIT_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_INITIALIZE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_DRAW_SUBMIT:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_FRAME:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_TERMINATE:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_UPDATE_OBJECTS:
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_SAMPLES:
			myBackend.setMsaaSamples(((RendererSetSamplesCommand*)myCommand)->samples);
			break;
		case Dynamik::RendererInstruction::RENDERER_INSTRUCTION_SET_WINDOW_HANDLE:
			myBackend.setWindowHandle(((RendererSetWindowHandleCommand*)myCommand)->windowHandle);
			break;
		default:
			break;
		}
	}

	void DMKRenderer::onLoop()
	{
		myBackend.initializeDrawCall();
		myBackend.updateRenderables();
		myBackend.submitRenderables();
	}

	void DMKRenderer::onTermination()
	{
		DMK_INFO("Terminated the renderer thread!");
	}
}
