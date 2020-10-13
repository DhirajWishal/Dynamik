-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Vulkan Renderer Backend Layer project description ----------

project "VulkanRBL"
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
		"%{IncludeLib.Vulkan}",
		"%{IncludeLib.GLFW}",
		"%{IncludeLib.GLEW}",
	}

	links { 
		"ImGui",
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