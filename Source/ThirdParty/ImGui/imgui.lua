---------- Dynamik Engine Support Library: Dear ImGui ----------
-- This library is forked and cloned from https://github.com/ocornut/imgui --

project "ImGui"
	kind "StaticLib"
	language "C++"
	systemversion "latest"
    cppdialect "C++17"
	staticruntime "On"

	targetdir "$(SolutionDir)Builds/ThirdParty/Binaries/$(Configuration)-$(Platform)/$(ProjectName)"
	objdir "$(SolutionDir)Builds/ThirdParty/Intermediate/$(Configuration)-$(Platform)/$(ProjectName)"

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
		"$(SolutionDir)Engine/ThirdParty/ImGui",
	}

    filter "files:/misc/**.**"
        flags "ExcludeFromBuild"

    filter "files:/examples/**.**"
        flags "ExcludeFromBuild"

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
