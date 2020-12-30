-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Asset Loader Tests project description ----------

project "AssetLoaderTests"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "On"
	systemversion "latest"

	targetdir "$(SolutionDir)Builds/Tests/Binaries/$(Configuration)-$(Platform)/$(ProjectName)"
	objdir "$(SolutionDir)Builds/Tests/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua"
	}

	includedirs {
		"$(SolutionDir)Core",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.GLFW}",
	}

	links {
		"AssetLoader",
	}
