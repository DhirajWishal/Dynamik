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
		io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
		io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;  // We can create multi-viewports on the Renderer side (optional)

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
	}

	void DMKImGuiWrapper::draw()
	{
		static struct UISettings {
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
	}

	void DMKImGuiWrapper::terminate()
	{
		ImGui::DestroyContext();
	}

	void DMKImGuiWrapper::update()
	{
		myImGuiBackend->setDrawData(ImGui::GetDrawData());

		auto& io = ImGui::GetIO();

		auto mousePos = DMKEventPool::getMousePosition();
		io.MousePos = ImVec2(mousePos.x, mousePos.y);

		io.MouseDown[0] = DMKEventPool::MouseButtonLeft.isPressed();
		io.MouseDown[1] = DMKEventPool::MouseButtonRight.isPressed();

		auto check = io.WantCaptureMouse;

		auto pDrawData = ImGui::GetDrawData();

		myImGuiBackend->uniformData.scale = Vector2F(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
		myImGuiBackend->uniformData.transform[0] = -1.0f - pDrawData->DisplayPos.x * myImGuiBackend->uniformData.scale[0];
		myImGuiBackend->uniformData.transform[1] = -1.0f - pDrawData->DisplayPos.y * myImGuiBackend->uniformData.scale[1];
	}
}
