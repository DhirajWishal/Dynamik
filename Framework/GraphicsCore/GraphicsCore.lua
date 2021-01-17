-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Graphics Core project description ----------

project "GraphicsCore"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

	defines {
		"DMK_INTERNAL"
	}

	targetdir "$(SolutionDir)Builds/Framework/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Framework/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua",
		"**.txt",
		"**.md",
	}

	includedirs {
		"$(SolutionDir)Framework/",
		"%{IncludeDir.stb}",
	}

	libdirs {
	}

	links { 
		"Core",
		"Inputs",
		"ShaderTools",
	}
