-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Input Tests project description ----------

project "InputTests"
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
		"$(SolutionDir)Core"
	}

	links {
		"Inputs"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DMK_PLATFORM_WINDOWS"
		}