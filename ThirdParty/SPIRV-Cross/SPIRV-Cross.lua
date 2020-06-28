---------- Dynamik Engine Support Library: SPIRV-Cross ----------
-- This library is forked and cloned from https://github.com/ocornut/imgui --

project "SPIRV-Cross"
	kind "StaticLib"
	language "C++"
	systemversion "latest"

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)/$(ProjectName)"
	objdir "$(SolutionDir)Builds/Engine/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

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
		"$(SolutionDir)Engine/ThirdParty/SPIRV-Cross",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"

		defines {
			"DMK_PLATFORM_WINDOWS",
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
		defines { "DMK_DEBUG"}
		symbols "On"

	filter "configurations:Debug Studio*"
		defines { "DMK_DEBUG", "DMK_BUILD_STUDIO" }
		symbols "On"
		
	filter "configurations:Release Engine*"
		defines { "DMK_RELEASE"}
		optimize "On"

	filter "configurations:Release Studio*"
		defines { "DMK_RELEASE", "DMK_BUILD_STUDIO"}
		optimize "On"

	filter "configurations:Distribution Engine*"
		defines { "DMK_DISTRIBUTION" }
		optimize "On"

	filter "configurations:Distribution Studio*"
		defines { "DMK_DISTRIBUTION" , "DMK_BUILD_STUDIO" }
		optimize "On"
