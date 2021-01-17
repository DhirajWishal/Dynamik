-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Image Loader project description ----------

project "ImageLoader"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

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
		"%{IncludeDir.stb}",
	}

	libdirs {
	}

	links { 
	}
