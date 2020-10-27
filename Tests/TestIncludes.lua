-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

-- File including all the test modules.

group "Tests"
include "CoreTests/CoreTests.lua"
include "GameLibraryTests/GameLibraryTests.lua"
include "GraphicsTests/GraphicsTests.lua"
include "InputTests/InputTests.lua"
include "VulkanBackendTests/VulkanBackendTests.lua"

include "Demos/DemosIncludes.lua"
