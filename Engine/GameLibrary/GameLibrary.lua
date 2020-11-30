-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Game Library project description ----------

project "GameLibrary"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

	defines {
		"DMK_INTERNAL",
		"GLFW_INCLUDE_VULKAN"
	}

	targetdir "$(SolutionDir)Builds/Core/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Core/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua",
		"**.txt",
		"**.md",
	}

	includedirs {
		"$(SolutionDir)Core/",
		"$(SolutionDir)Engine/",
	}

	libdirs {
	}

	links { 
		"Graphics",
	}
