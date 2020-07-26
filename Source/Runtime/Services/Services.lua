-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Services project description ----------

project "Services"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

	defines {
		"DMK_INTERNAL"
	}

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)/$(ProjectName)"
	objdir "$(SolutionDir)Builds/Engine/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	pchheader "dmkafx.h"
	pchsource "../Core/PCH/dmkafx.cpp"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua",
		"**.txt",
		"**.md",
	}

	includedirs {
		"$(SolutionDir)Dependencies/Libraries/Local",
		"$(SolutionDir)Source/Runtime/",
		"$(SolutionDir)Source/Runtime/Core/PCH/",
	}

	libdirs {
	}

	links { 
	}

	filter "system:windows"
		defines {
			"DMK_PLATFORM_WINDOWS",
		}

	filter "system:linux"
		defines {
			"DMK_PLATFORM_LINUX",
		}

	filter "system:macosx"
		defines {
			"DMK_PLATFORM_MAC",
		}