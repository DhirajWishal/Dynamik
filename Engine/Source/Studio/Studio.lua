---------- Studio project ----------

project "Studio"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	--staticruntime "On"
	clr "On"

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Engine/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	pchheader "studioafx.h"
	pchsource "Core/PCH/studioafx.cpp"

	files {
		"**.h",
		"**.cpp",
		"**.lua"
	}

	includedirs {
		"$(SolutionDir)Dependencies/Libraries/Local",
		"$(SolutionDir)Engine/Source/Studio/",
		"$(SolutionDir)Engine/Source/Studio/Core/",
		"$(SolutionDir)Engine/Source/Studio/Core/PCH/",
		"$(SolutionDir)Engine/Source/Runtime/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/GameLibraries",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
	}

	libdirs {
		"%{IncludeLib.GLFW}",
		"%{IncludeLib.GLEW}",
	}

	links { 
		"Dynamik",
		"glew32s",
		"opengl32",
		"glfw3dll",
		"glfw3"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"DMK_PLATFORM_WINDOWS",
			"GLEW_STATIC",
			"GRAPHICS_API",
		}

	filter "configurations:Debug"
		defines "DMK_DEBUG"
		--buildoptions "/MTd"
		symbols "On"
		
	filter "configurations:Release"
		defines "DMK_RELEASE"
		--buildoptions "/MT"
		optimize "On"

	filter "configurations:Distribution"
		defines "DMK_DISTRIBUTION"
		--buildoptions "/MT"
		optimize "On"
