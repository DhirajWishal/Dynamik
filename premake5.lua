workspace "Dynamik"
	architecture "x64"

	platforms { "Windows", "Unix", "Mac" }

	configurations {
		"Debug Engine",
		"Debug Studio",
		"Release Engine",
		"Release Studio",
		"Distribution Engine",
		"Distribution Studio"
	}

	filter "platforms:Windows"
		system "windows"

	filter "platforms:Unix"
		system "linux"

	filter "platforms:Mac"
		system "macosx"

outputDir = "$(Configuration)-$(Platform)"
solutionDir = "$(SolutionDir)"
configurationMacro = "$(Configuration)"
platformMacro = "$(Platform)"
projectNameMacro = "$(ProjectName)"

engineSourcePath = "$(SolutionDir)Engine/Source/"
engineOutputDir = "$(SolutionDir)Builds/Engine/"
engineOutputBinaryDir = "Binaries/"
engineOutputIntermediateDir = "Intermediate/"

IncludeDir = {}
IncludeDir["GLFW"] = "$(SolutionDir)Dependencies/Libraries/External/glfw/include"
IncludeDir["GLEW"] = "$(SolutionDir)Dependencies/GLEW/include"
IncludeDir["glm"] = "$(SolutionDir)Dependencies/Libraries/External/glm"
IncludeDir["stb"] = "$(SolutionDir)Dependencies/Libraries/External/stb"
IncludeDir["tol"] = "$(SolutionDir)Dependencies/Libraries/External/tinyobjloader"
IncludeDir["gli"] = "$(SolutionDir)Dependencies/Libraries/External/gli/gli"
IncludeDir["zlib"] = "$(SolutionDir)Dependencies/Libraries/External/zlib/"
IncludeDir["Vulkan"] = "$(SolutionDir)Dependencies/Libraries/External/Vulkan/include"
IncludeDir["imgui"] = "$(SolutionDir)Dependencies/Libraries/External/Vulkan/include"

IncludeDir["boost"] = "E:/Projects/Dynamik Engine/Libraries/boost_1_70_0"
IncludeDir["jpeg"] = "$(SolutionDir)Dependencies/Libraries/Local/gil/jpeg-6b"
IncludeDir["irrKlang"] = "$(SolutionDir)Dependencies/Libraries/Local/irrKlang/include"
IncludeDir["assimp"] = "$(SolutionDir)Dependencies/Libraries/Local/assimp"

IncludeLib = {}
IncludeLib["GLFW"] = "$(SolutionDir)Dependencies/Libraries/Binaries/GLFW/lib-vc2019"
IncludeLib["GLEW"] = "$(SolutionDir)Dependencies/Libraries/Binaries/GLEW/Release/x64"
IncludeLib["Vulkan"] = "$(SolutionDir)Dependencies/Libraries/Binaries/Vulkan"
IncludeLib["DirectX"] = "$(SolutionDir)Dependencies/Libraries/Binaries/DirectX12"
IncludeLib["irrKlang"] = "$(SolutionDir)Dependencies/Libraries/Binaries/irrKlang"
IncludeLib["boost"] = "E:/Projects/Dynamik Engine/Libraries/boost_1_70_0/stage/lib"
IncludeLib["Assimp"] = "$(SolutionDir)Dependencies/Libraries/Binaries/Assimp"
IncludeDir["zlib"] = "$(SolutionDir)Dependencies/Libraries/External/zlib//contrib/vstudio/vc14/x64/ZlibStatRelease"

group "Engine"	-- Add the Engine to a virtual folder
include "Engine/Source/Dynamik.lua"
include "Engine/Application/Application.lua"

group "Third Party"
include "Engine/ThirdParty/imgui/imgui.lua"

group ""
