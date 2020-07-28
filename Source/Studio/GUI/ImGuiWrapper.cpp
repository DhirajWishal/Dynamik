// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ImGuiWrapper.h"

#include "Services/SystemLocator.h"
#include "Renderer/Renderer.h"
#include "Core/Types/StaticArray.h"

#include <imgui.h>

namespace Dynamik
{
	DMKImGuiWrapper::DMKImGuiWrapper()
	{
	}

	DMKImGuiWrapper::~DMKImGuiWrapper()
	{
	}

	void DMKImGuiWrapper::initialize()
	{
		ImGui::CreateContext();

		// Dimensions
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(windowExtent.width, windowExtent.height);
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		// Color scheme
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
		style.Colors[ImGuiCol_Header] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	void DMKImGuiWrapper::initializeBackend()
	{
		DMKSystemLocator::getSystem<DMKRenderer>()->createImGuiClientCMD(&myImGuiBackend);

		while (myImGuiBackend == nullptr);

		DMK_INFO("Successfully created the im gui backend!");

		struct UISettings {
			bool displayModels = true;
			bool displayLogos = true;
			bool displayBackground = true;
			bool animateLight = false;
			float lightSpeed = 0.25f;
			StaticArray<float, 50> frameTimes{};
			float frameTimeMin = 9999.0f, frameTimeMax = 0.0f;
			float lightTimer = 0.0f;
		} uiSettings;

		{
			ImGui::NewFrame();

			ImGui::PlotLines("Frame Times", &uiSettings.frameTimes[0], 50, 0, "", uiSettings.frameTimeMin, uiSettings.frameTimeMax, ImVec2(0, 80));

			ImGui::Text("Camera");

			ImGui::SetNextWindowSize(ImVec2(200, 200));
			ImGui::Begin("Example settings");
			ImGui::Checkbox("Render models", &uiSettings.displayModels);
			ImGui::Checkbox("Display logos", &uiSettings.displayLogos);
			ImGui::Checkbox("Display background", &uiSettings.displayBackground);
			ImGui::Checkbox("Animate light", &uiSettings.animateLight);
			ImGui::SliderFloat("Light speed", &uiSettings.lightSpeed, 0.1f, 1.0f);
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(650, 20));
			ImGui::ShowDemoWindow();

			// Render to generate draw buffers
			ImGui::Render();
		}

		DMKSystemLocator::getSystem<DMKRenderer>()->submitImGuiDrawData(ImGui::GetDrawData());

		myImGuiBackend->setDrawData(ImGui::GetDrawData());
	}

	void DMKImGuiWrapper::terminate()
	{
		ImGui::DestroyContext();
	}

	void DMKImGuiWrapper::update()
	{
		myImGuiBackend->setDrawData(ImGui::GetDrawData());
	}
}
