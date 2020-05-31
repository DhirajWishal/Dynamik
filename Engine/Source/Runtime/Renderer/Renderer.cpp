#include "dmkafx.h"
#include "Renderer.h"

namespace Dynamik
{
	DMKRenderer::DMKRenderer()
	{
	}

	DMKRenderer::~DMKRenderer()
	{
	}

	void DMKRenderer::setMsaaSamples(DMKSampleCount msaaSamples)
	{
	}

	void DMKRenderer::setWindowHandle(POINTER<DMKWindowHandle> handle)
	{
		myBackend.setWindowHandle(handle);
	}

	void DMKRenderer::initialize()
	{
		myBackend.initializeCore();
	}

	void DMKRenderer::initializeObjects(const POINTER<DMKLevelComponent>& level)
	{
	}

	void DMKRenderer::initializeDraw()
	{
		myBackend.initializeDrawCall();
	}

	void DMKRenderer::updateObjects()
	{
		myBackend.updateRenderables();
	}

	void DMKRenderer::submitObjects()
	{
		myBackend.submitRenderables();
	}
	
	void DMKRenderer::terminate()
	{
	}
}