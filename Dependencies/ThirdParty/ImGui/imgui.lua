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
		"LICENSE.txt",
		"imconfig.h",
		"imgui.cpp",
		"imgui.h",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_internal.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imgui_rectpack.cpp",
		"imgui_rectpack.h",
		"imgui_textedit.h",
		"imgui_truetype.h",
		"imgui.lua",
	}

	includedirs {
		"$(SolutionDir)Dependencies/Libraries/Local",
		"$(SolutionDir)Engine/ThirdParty/ImGui",
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
