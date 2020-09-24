-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

workspace "Dynamik"
	architecture "x64"

	platforms { "Windows", "Unix", "Mac" }

	configurations {
		"Debug",
		"Release",
		"Distribution",
	}

	filter "platforms:Windows"
		system "windows"

	filter "platforms:Unix"
		system "linux"

	filter "platforms:Mac"
		system "macosx"

	filter "configurations:Debug"
		defines { "DMK_DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "DMK_RELEASE" }
		optimize "On"

	filter "configurations:Distribution"
		defines { "DMK_DISTRIBUTION" }
		optimize "On"

outputDir = "$(Configuration)-$(Platform)"
solutionDir = "$(SolutionDir)"
configurationMacro = "$(Configuration)"
platformMacro = "$(Platform)"
projectNameMacro = "$(ProjectName)"

engineSourcePath = "$(SolutionDir)Engine/Source/"
engineOutputDir = "$(SolutionDir)Builds/Engine/"
engineOutputBinaryDir = "Binaries/"
engineOutputIntermediateDir = "Intermediate/"

-- Libraries
IncludeDir = {}
IncludeDir["GLFW"] = "$(SolutionDir)Dependencies/ThirdParty/glfw/include"
IncludeDir["GLEW"] = "$(SolutionDir)Dependencies/GLEW/include"
IncludeDir["stb"] = "$(SolutionDir)Dependencies/ThirdParty/stb"
IncludeDir["glm"] = "$(SolutionDir)Dependencies/ThirdParty/gli/external/glm"
IncludeDir["gli"] = "$(SolutionDir)Dependencies/ThirdParty/gli"
IncludeDir["zlib"] = "$(SolutionDir)Dependencies/Libraries/External/zlib/"
IncludeDir["Vulkan"] = "$(SolutionDir)Dependencies/ThirdParty/Vulkan/include"
IncludeDir["SPIRVTools"] = "$(SolutionDir)Dependencies/ThirdParty/SPIRV-Tools/include"
IncludeDir["glslang"] = "$(SolutionDir)Dependencies/ThirdParty/glslang/"
IncludeDir["FreeImage"] = "$(SolutionDir)Dependencies/ThirdParty/FreeImage/Include"

IncludeDir["boost"] = "E:/Dynamik/Libraries/boost_1_70_0"
IncludeDir["jpeg"] = "$(SolutionDir)Dependencies/ThirdParty/gil/jpeg-6b"
IncludeDir["irrKlang"] = "$(SolutionDir)Dependencies/Libraries/Local/irrKlang/include"
IncludeDir["assimp"] = "$(SolutionDir)Dependencies/ThirdParty/Assimp/include"

-- Binaries
IncludeLib = {}
IncludeLib["GLFW"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/GLFW/lib-vc2019"
IncludeLib["GLEW"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/GLEW/Release/x64"
IncludeLib["Vulkan"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/Vulkan"
IncludeLib["DirectX"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/DirectX12"
IncludeLib["irrKlang"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/irrKlang"
IncludeLib["boost"] = "E:/Dynamik/Libraries/boost_1_70_0/stage/lib"
IncludeLib["Assimp"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/Assimp"
IncludeLib["SPIRVTools"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/SPIRV-Tools/"
IncludeLib["zlib"] = ""	-- TODO
IncludeLib["glslang"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/glslang/"
IncludeLib["FreeImageD"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/FreeImage/Debug"
IncludeLib["FreeImageR"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/FreeImage/Release"

group "Engine"
include "Engine/Modules/Animation/Animation.lua"
include "Engine/Modules/Core/Core.lua"
include "Engine/Modules/Events/Events.lua"
include "Engine/Modules/GameLibrary/GameLibrary.lua"
include "Engine/Modules/Importer/Importer.lua"
include "Engine/Modules/Managers/Managers.lua"
include "Engine/Modules/Renderer/Renderer.lua"
include "Engine/Modules/Services/Services.lua"
include "Engine/Modules/Tools/Tools.lua"
include "Engine/Modules/UserInterface/UserInterface.lua"
include "Engine/Modules/VulkanRBL/VulkanRBL.lua"
include "Engine/Modules/Window/Window.lua"

group "Studio"
include "Studio/Application/Application.lua"

group "Third Party"
include "Dependencies/ThirdParty/imgui/imgui.lua"
include "Dependencies/ThirdParty/SPIRV-Cross/SPIRV-Cross.lua"

group ""