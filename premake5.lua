workspace "Lambda"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Lambda/vendor/GLFW/include"
IncludeDir["Glad"] = "Lambda/vendor/Glad/include"
IncludeDir["ImGui"] = "Lambda/vendor/imgui"

include "Lambda/vendor/GLFW"
include "Lambda/vendor/Glad"
include "Lambda/vendor/imgui"


project "Lambda"
	location "Lambda"
	kind "SharedLib"
	language "C++"
	staticruntime "off"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lmpch.h"
	pchsource "Lambda/src/lmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"Lambda/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",

	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LM_PLATFORM_WINDOWS",
			"LM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

		filter "configurations:Debug"
			defines "LM_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "LM_RELEASE"
			runtime "Release"
			optimize "On"
		
		filter "configurations:Dist"
			defines "LM_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Lambda/vendor/spdlog/include",
		"Lambda/src"
	}

	links
	{
		"Lambda"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LM_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "LM_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "LM_RELEASE"
			runtime "Release"
			optimize "On"
		
		filter "configurations:Dist"
			defines "LM_DIST"
			runtime "Release"
			optimize "On"
