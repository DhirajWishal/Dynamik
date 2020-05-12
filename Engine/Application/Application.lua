---------- Application project description ----------

project "Application"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)"
	objdir "$(SolutionDir)Builds/Engine/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

	files {
		"**.txt",
		"**.cpp",
		"**.h",
		"src/**.cpp",
		"src/**.h",
		"**.lua"
	}

	includedirs {
		"$(SolutionDir)Dependencies/Libraries/Local",
		"$(SolutionDir)Engine/Source/Runtime/",
		"$(SolutionDir)Engine/Source/Runtime/Core/",
		"$(SolutionDir)Engine/Source/Runtime/GameLibraries",
		"$(SolutionDir)Engine/Source/Runtime/Core/Algorithm",
		"$(SolutionDir)Engine/Source/Runtime/Core/DataTypes",
		"$(SolutionDir)Engine/Source/Runtime/Core/Math",
		"$(SolutionDir)Engine/Source/Runtime/Core/Memory",
		"$(SolutionDir)Engine/Source/Runtime/Core/System",
	}

	links {
		"Dynamik"
	}

	filter "system:windows"
		staticruntime "On"
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