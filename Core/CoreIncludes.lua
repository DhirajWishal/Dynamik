-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

-- File including all the core modules.

group "Core"
include "Animation/Animation.lua"
include "Core/Core.lua"
include "Engine/Engine.lua"
include "Events/Events.lua"
include "GameLibrary/GameLibrary.lua"
include "Importer/Importer.lua"
include "Managers/Managers.lua"
include "Renderer/Renderer.lua"
include "Services/Services.lua"
include "Tools/Tools.lua"
include "UserInterface/UserInterface.lua"
include "VulkanRBL/VulkanRBL.lua"
include "Window/Window.lua"

group "Core/NewArchitecture"
include "GraphicsCore/GraphicsCore.lua"
include "GraphicsEngine/GraphicsEngine.lua"
include "Inputs/Inputs.lua"
include "VulkanBackend/VulkanBackend.lua"
