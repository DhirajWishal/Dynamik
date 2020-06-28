-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Window project description ----------

project "Window"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"

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
		"$(SolutionDir)ThirdParty/imgui",
		"$(SolutionDir)ThirdParty/SPIRV-Cross",
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

		defines {
			"DMK_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_VULKAN",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "system:linux"

		defines {
			"DMK_PLATFORM_LINUX",
			"GLFW_INCLUDE_VULKAN",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "system:macosx"

		defines {
			"DMK_PLATFORM_MAC",
			"GLFW_INCLUDE_VULKAN",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "configurations:Debug"
		defines { "DMK_DEBUG"}
		symbols "On"
		
	filter "configurations:Release"
		defines { "DMK_RELEASE"}
		optimize "On"

	filter "configurations:Distribution"
		defines { "DMK_DISTRIBUTION" }
		optimize "On"