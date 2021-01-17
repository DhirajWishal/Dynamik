-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Asset Loader project description ----------

project "AssetLoader"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

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
		"%{IncludeDir.FreeImage}",
	}

	filter "configurations:Debug"
		libdirs {
			"%{IncludeLib.FreeImageD}",
		}

		links { 
			"GraphicsCore",
			"FreeImageLibd",
		}
		
	filter "configurations:Release"
		libdirs {
			"%{IncludeLib.FreeImageR}",
		}

		links { 
			"GraphicsCore",
			"FreeImageLib",
		}

	filter ""