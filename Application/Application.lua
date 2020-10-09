-- Copyright 2020 Dhiraj Wishal
-- SPDX-License-Identifier: Apache-2.0

---------- Application project description ----------

project "Application"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"

	targetdir "$(SolutionDir)Builds/Engine/Binaries/$(Configuration)-$(Platform)/$(ProjectName)"
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
		"$(SolutionDir)Source/Engine/",
		"$(SolutionDir)Source/Runtime/",
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

	links {
		"DynamikEngine"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"DMK_PLATFORM_WINDOWS"
		}