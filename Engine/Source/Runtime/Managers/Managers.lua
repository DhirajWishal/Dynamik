-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Managers project description ----------

project "Managers"
	language "C++"
	systemversion "latest"
	kind "StaticLib"
	location "../../../Programs"

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
		"$(SolutionDir)Engine/Source/Runtime/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/Core/PCH/",
		"$(SolutionDir)Engine/Source/Runtime/GameLibraries",
		"$(SolutionDir)Engine/ThirdParty/imgui",
		"$(SolutionDir)Engine/ThirdParty/SPIRV-Cross",
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
		"%{IncludeLib.Vulkan}",
		"%{IncludeLib.GLFW}",
		"%{IncludeLib.GLEW}",
	}

	links { 
		"glew32s",
		"opengl32",
		"glfw3dll",
		"vulkan-1",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"

		defines {
			"DMK_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_VULKAN",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"

		defines {
			"DMK_PLATFORM_LINUX",
			"GLFW_INCLUDE_VULKAN",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "system:macosx"
		cppdialect "C++17"
		staticruntime "On"

		defines {
			"DMK_PLATFORM_MAC",
			"GLFW_INCLUDE_VULKAN",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "configurations:Debug Engine*"
		defines { "DMK_DEBUG", "DMK_BUILD_ENGINE" }
		symbols "On"

	filter "configurations:Debug Studio*"
		defines { "DMK_DEBUG", "DMK_BUILD_STUDIO" }
		symbols "On"
		
	filter "configurations:Release Engine*"
		defines { "DMK_RELEASE", "DMK_BUILD_ENGINE"}
		optimize "On"

	filter "configurations:Release Studio*"
		defines { "DMK_RELEASE", "DMK_BUILD_STUDIO"}
		optimize "On"

	filter "configurations:Distribution Engine*"
		defines { "DMK_DISTRIBUTION" , "DMK_BUILD_ENGINE" }
		optimize "On"

	filter "configurations:Distribution Studio*"
		defines { "DMK_DISTRIBUTION" , "DMK_BUILD_STUDIO" }
		optimize "On"