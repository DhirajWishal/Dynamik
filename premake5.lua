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

	filter {}

	filter "configurations:Debug"
		defines { "DMK_DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "DMK_RELEASE" }
		optimize "On"

	filter "configurations:Distribution"
		defines { "DMK_DISTRIBUTION" }
		optimize "On"

	filter {}

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
IncludeDir["glm"] = "$(SolutionDir)Dependencies/ThirdParty/glm"
IncludeDir["stb"] = "$(SolutionDir)Dependencies/ThirdParty/stb"
IncludeDir["gli"] = "$(SolutionDir)Dependencies/ThirdParty/gli/gli"
IncludeDir["zlib"] = "$(SolutionDir)Dependencies/Libraries/External/zlib/"
IncludeDir["Vulkan"] = "$(SolutionDir)Dependencies/ThirdParty/Vulkan/include"
IncludeDir["SPIRVTools"] = "$(SolutionDir)Dependencies/ThirdParty/SPIRV-Tools/include"
IncludeDir["glslang"] = "$(SolutionDir)Dependencies/Libraries/External/glslang"

IncludeDir["boost"] = "E:/Projects/Dynamik Engine/Libraries/boost_1_70_0"
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
IncludeLib["boost"] = "E:/Projects/Dynamik Engine/Libraries/boost_1_70_0/stage/lib"
IncludeLib["Assimp"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/Assimp"
IncludeLib["SPIRVTools"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/SPIRV-Tools/"
IncludeLib["zlib"] = ""	-- TODO
IncludeLib["glslang"] = "$(SolutionDir)Dependencies/ThirdParty/Binaries/glslang/lib"


group "Engine"	-- Add the Engine to a virtual folder
include "Source/Engine/DynamikEngine.lua"
include "Application/Application.lua"

group "Studio"
include "Source/Studio/DynamikStudio.lua"

group "Runtime"
include "Source/Runtime/Animation/Animation.lua"
include "Source/Runtime/ComponentSystem/ComponentSystem.lua"
include "Source/Runtime/Core/Core.lua"
include "Source/Runtime/Events/Events.lua"
include "Source/Runtime/GameLibrary/GameLibrary.lua"
include "Source/Runtime/Importer/Importer.lua"
include "Source/Runtime/Managers/Managers.lua"
include "Source/Runtime/Renderer/Renderer.lua"
include "Source/Runtime/Services/Services.lua"
include "Source/Runtime/Tools/Tools.lua"
include "Source/Runtime/VulkanRBL/VulkanRBL.lua"
include "Source/Runtime/Window/Window.lua"

group "Third Party"
include "Dependencies/ThirdParty/imgui/imgui.lua"
include "Dependencies/ThirdParty/SPIRV-Cross/SPIRV-Cross.lua"

group ""
