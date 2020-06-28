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

	filter ""

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
IncludeDir["GLFW"] = "$(SolutionDir)Dependencies/Libraries/External/glfw/include"
IncludeDir["GLEW"] = "$(SolutionDir)Dependencies/GLEW/include"
IncludeDir["glm"] = "$(SolutionDir)Dependencies/Libraries/External/glm"
IncludeDir["stb"] = "$(SolutionDir)Dependencies/Libraries/External/stb"
IncludeDir["tol"] = "$(SolutionDir)Dependencies/Libraries/External/tinyobjloader"
IncludeDir["gli"] = "$(SolutionDir)Dependencies/Libraries/External/gli/gli"
IncludeDir["zlib"] = "$(SolutionDir)Dependencies/Libraries/External/zlib/"
IncludeDir["Vulkan"] = "$(SolutionDir)Dependencies/Libraries/External/Vulkan/include"
IncludeDir["SPIRVTools"] = "$(SolutionDir)Dependencies/Libraries/External/SPIRV-Tools/include"
IncludeDir["glslang"] = "$(SolutionDir)Dependencies/Libraries/External/glslang"

IncludeDir["boost"] = "E:/Projects/Dynamik Engine/Libraries/boost_1_70_0"
IncludeDir["jpeg"] = "$(SolutionDir)Dependencies/Libraries/Local/gil/jpeg-6b"
IncludeDir["irrKlang"] = "$(SolutionDir)Dependencies/Libraries/Local/irrKlang/include"
IncludeDir["assimp"] = "$(SolutionDir)Dependencies/Libraries/Local/assimp"

-- Binaries
IncludeLib = {}
IncludeLib["GLFW"] = "$(SolutionDir)Dependencies/Libraries/Binaries/GLFW/lib-vc2019"
IncludeLib["GLEW"] = "$(SolutionDir)Dependencies/Libraries/Binaries/GLEW/Release/x64"
IncludeLib["Vulkan"] = "$(SolutionDir)Dependencies/Libraries/Binaries/Vulkan"
IncludeLib["DirectX"] = "$(SolutionDir)Dependencies/Libraries/Binaries/DirectX12"
IncludeLib["irrKlang"] = "$(SolutionDir)Dependencies/Libraries/Binaries/irrKlang"
IncludeLib["boost"] = "E:/Projects/Dynamik Engine/Libraries/boost_1_70_0/stage/lib"
IncludeLib["Assimp"] = "$(SolutionDir)Dependencies/Libraries/Binaries/Assimp"
IncludeLib["zlib"] = "$(SolutionDir)Dependencies/Libraries/External/zlib//contrib/vstudio/vc14/x64/ZlibStatRelease"
IncludeLib["SPIRVTools"] = "$(SolutionDir)Dependencies/Libraries/External/SPIRV-Tools/lib"
IncludeLib["glslang"] = "$(SolutionDir)Dependencies/Libraries/External/glslang/lib"


group "Engine"	-- Add the Engine to a virtual folder
include "Source/Engine/DynamikEngine.lua"
include "Application/Application.lua"

group "Studio"
include "Source/Studio/DynamikStudio.lua"

group "Runtime"
include "Source/Runtime/ComponentSystem/ComponentSystem.lua"
include "Source/Runtime/Core/Core.lua"
include "Source/Runtime/Events/Events.lua"
include "Source/Runtime/GameLibrary/GameLibrary.lua"
include "Source/Runtime/Importer/Importer.lua"
include "Source/Runtime/Managers/Managers.lua"
include "Source/Runtime/Renderer/Renderer.lua"
include "Source/Runtime/Tools/Tools.lua"
include "Source/Runtime/Window/Window.lua"

group "Third Party"
include "ThirdParty/imgui/imgui.lua"
include "ThirdParty/SPIRV-Cross/SPIRV-Cross.lua"

group ""
