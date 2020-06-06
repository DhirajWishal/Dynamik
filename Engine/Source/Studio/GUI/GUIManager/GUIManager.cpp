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
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
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
