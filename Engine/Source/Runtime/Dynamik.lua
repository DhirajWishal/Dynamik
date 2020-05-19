---------- Dynamik Engine project description ----------

project "Dynamik"
	kind "StaticLib"
	language "C++"
	systemversion "latest"

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Engine/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	pchheader "dmkafx.h"
	pchsource "Core/PCH/dmkafx.cpp"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"**.lua",
		"**.txt"
	}

	includedirs {
		"$(SolutionDir)Dependencies/Libraries/Local",
		"$(SolutionDir)Engine/Source/Runtime/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/Core/PCH/",
		"$(SolutionDir)Engine/Source/Runtime/GameLibraries",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
	}

	libdirs {
		"%{IncludeLib.GLFW}",
		"%{IncludeLib.GLEW}",
	}

	links { 
		"glew32s",
		"opengl32",
		"glfw3dll",
		"glfw3"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"

		defines {
			"DMK_PLATFORM_WINDOWS",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "configurations:Debug"
		defines "DMK_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "DMK_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "DMK_DISTRIBUTION"
		optimize "On"