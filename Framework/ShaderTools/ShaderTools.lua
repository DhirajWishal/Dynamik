-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Shader Tools project description ----------

project "ShaderTools"
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
		"$(SolutionDir)Dependencies/ThirdParty/SPIRV-Cross",
	}

	libdirs {
	}

	links { 
		"SPIRV-Cross",
	}