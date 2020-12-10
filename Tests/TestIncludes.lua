-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

-- File including all the test modules.

group "Tests"
include "AudioTests/AudioTests.lua"
include "CoreTests/CoreTests.lua"
include "GameLibraryTests/GameLibraryTests.lua"
include "GraphicsCoreTests/GraphicsCoreTests.lua"
include "GraphicsTests/GraphicsTests.lua"
include "InputTests/InputTests.lua"
include "IntellectTests/IntellectTests.lua"
include "ShaderToolsTests/ShaderToolsTests.lua"
include "ThreadTests/ThreadTests.lua"
include "VulkanBackendTests/VulkanBackendTests.lua"
include "XAudio2BackendTests/XAudio2BackendTests.lua"

include "Demos/DemosIncludes.lua"
