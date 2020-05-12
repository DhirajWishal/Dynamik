---------- Studio project ----------

project "Studio"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "On"

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
		"$(SolutionDir)Engine/Studio/",
		"$(SolutionDir)Engine/Studio/Core/PCH/",
		"$(SolutionDir)Engine/Source/Runtime/",
		"$(SolutionDir)Engine/Source/Runtime/Core/Algorithm",
		"$(SolutionDir)Engine/Source/Runtime/Core/DataTypes",
		"$(SolutionDir)Engine/Source/Runtime/Core/Memory",
		"$(SolutionDir)Engine/Source/Runtime/Core/System",
		"$(SolutionDir)Engine/Source/Runtime/GameLibraries",
	}

	libdirs {
	}

	links { 
		"Dynamik"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"DMK_PLATFORM_WINDOWS"
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
