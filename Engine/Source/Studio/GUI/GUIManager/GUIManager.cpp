#include "dmkafx.h"
#include "GUIManager.h"
#include "Window/Windows/WindowsWindow.h"

#include "imgui.h"

namespace Dynamik
{
	GUIManager::GUIManager()
	{
		windowHandle = (POINTER<DMKWindowHandle>)StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow("Dynamik Studio v1", 1280, 720));
		windowHandle->initialize();
		ImGui::CreateContext();
	}
	
	GUIManager::~GUIManager()
	{
		windowHandle->terminate();
		StaticAllocator<DMKWindowHandle>::deallocate(windowHandle, 0);
	}

	void GUIManager::initialize()
	{
	}

	void GUIManager::beginFrame()
	{
	}

	void GUIManager::onUpdate()
	{
	}

	void GUIManager::endFrame()
	{
	}

	void GUIManager::terminate()
	{
	}
}
