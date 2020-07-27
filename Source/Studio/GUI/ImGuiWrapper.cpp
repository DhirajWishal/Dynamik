// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ImGuiWrapper.h"

#include "Services/SystemLocator.h"
#include "Renderer/Renderer.h"

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

		// Color scheme
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
		style.Colors[ImGuiCol_Header] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

		// Dimensions
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(windowExtent.width, windowExtent.height);
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	}

	void DMKImGuiWrapper::initializeBackend()
	{
		DMKSystemLocator::getSystem<DMKRenderer>()->createImGuiClientCMD(&myImGuiBackend);

		while (myImGuiBackend == nullptr);

		DMK_INFO("Successfully created the im gui backend!");
	}

	void DMKImGuiWrapper::terminate()
	{
		ImGui::DestroyContext();
	}
	
	void DMKImGuiWrapper::update()
	{
		myImGuiBackend->update(ImGui::GetDrawData());
	}
}
