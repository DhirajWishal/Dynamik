-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Animation project description ----------

project "Animation"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

	defines {
		"DMK_INTERNAL"
	}

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)"
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
		"$(SolutionDir)Engine/Modules/",
		"$(SolutionDir)Engine/Modules/Core/PCH/",
		"$(SolutionDir)Dependencies/ThirdParty/imgui",
		"$(SolutionDir)Dependencies/ThirdParty/SPIRV-Cross",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.gli}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.zlib}",
		"%{IncludeDir.SPIRVTools}",
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