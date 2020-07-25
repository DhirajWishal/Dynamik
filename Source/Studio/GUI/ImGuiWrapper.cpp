// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ImGuiWrapper.h"

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
	}

	void DMKImGuiWrapper::terminate()
	{
		ImGui::DestroyContext();
	}
}
