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
		ImGuiIO& io = ImGui::GetIO();
		IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

		// Setup display size (every frame to accommodate for window resizing)
		int w, h;
		int display_w, display_h;
		glfwGetWindowSize(((POINTER<WindowsWindow>)windowHandle)->getWindowHandle(), &w, &h);
		glfwGetFramebufferSize(((POINTER<WindowsWindow>)windowHandle)->getWindowHandle(), &display_w, &display_h);
		io.DisplaySize = ImVec2((float)w, (float)h);
		if (w > 0 && h > 0)
			io.DisplayFramebufferScale = ImVec2((float)display_w / w, (float)display_h / h);

		// Setup time step
		double current_time = glfwGetTime();
		io.DeltaTime = time > 0.0 ? (float)(current_time - time) : (float)(1.0f / 60.0f);
		time = current_time;

		ImGui::NewFrame();
	}

	void GUIManager::onUpdate()
	{
		ImGui::Begin("Hello, world!");
	}

	void GUIManager::endFrame()
	{
		ImGui::Render();
	}

	void GUIManager::terminate()
	{
	}
}
