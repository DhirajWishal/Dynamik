-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Game Library Tests project description ----------

project "GameLibraryTests"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"

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
		"$(SolutionDir)Engine",
	}

	links {
		"GameLibrary",
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DMK_PLATFORM_WINDOWS"
		}