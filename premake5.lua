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

	--defines { "DMK_USE_WIDE_CHAR" }

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
IncludeDir["SDL2"] = "$(SolutionDir)Dependencies/ThirdParty/SDL2-2.0.12/include"
IncludeDir["xxhash"] = "$(SolutionDir)Dependencies/ThirdParty/xxhash/include"

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
IncludeLib["SDL2"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/SDL2-2.0.12/bin/x64/"
IncludeLib["xxhash"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/xxhash/lib/"

IncludeLib["zlib"] = ""	-- TODO
IncludeLib["glslang"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/glslang/"
IncludeLib["FreeImageD"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/FreeImage/Debug"
IncludeLib["FreeImageR"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/FreeImage/Release"

group "Framework"
include "Framework/AssetLoader/AssetLoader.lua"
include "Framework/Audio/Audio.lua"
include "Framework/AudioCore/AudioCore.lua"
include "Framework/Core/Core.lua"
include "Framework/Graphics/Graphics.lua"
include "Framework/GraphicsCore/GraphicsCore.lua"
include "Framework/Inputs/Inputs.lua"
include "Framework/Intellect/Intellect.lua"
include "Framework/ShaderTools/ShaderTools.lua"
include "Framework/Thread/Thread.lua"
include "Framework/VulkanBackend/VulkanBackend.lua"
include "Framework/XAudio2Backend/XAudio2Backend.lua"

group "Demos"

group "Third Party"
include "Dependencies/ThirdParty/SPIRV-Cross/SPIRV-Cross.lua"
--include "Dependencies/ThirdParty/imgui/imgui.lua"

group ""