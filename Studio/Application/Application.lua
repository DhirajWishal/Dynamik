-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Application project description ----------

project "Application"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"

	defines {
		"DMK_INTERNAL"
	}

	targetdir "$(SolutionDir)Builds/Studio/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Studio/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	pchheader "dmkafx.h"
	pchsource "../Core/PCH/dmkafx.cpp"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.md",
		"**.ini",
		"**.lua"
	}

	includedirs {
		"$(SolutionDir)Dependencies/Libraries/Local",
		"$(SolutionDir)Core/",
		"$(SolutionDir)Core/Core/PCH/",
		"$(SolutionDir)Dependencies/ThirdParty/imgui",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.assimp}",
	}

	links {
		"Animation",
		"Core",
		"Events",
		"GameLibrary",
		"Importer",
		"Managers",
		"Renderer",
		"Services",
		"Tools",
		"UserInterface",
		"Window",

		"ImGui",
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DMK_PLATFORM_WINDOWS"
		}