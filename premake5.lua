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
IncludeDir["glm"] = "Lambda/vendor/glm"

include "Lambda/vendor/GLFW"
include "Lambda/vendor/Glad"
include "Lambda/vendor/imgui"


project "Lambda"
	location "Lambda"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lmpch.h"
	pchsource "Lambda/src/lmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LM_PLATFORM_WINDOWS",
			"LM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "LM_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "LM_RELEASE"
			runtime "Release"
			optimize "on"
		
		filter "configurations:Dist"
			defines "LM_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Lambda/src",
		"Lambda/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Lambda"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LM_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "LM_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "LM_RELEASE"
			runtime "Release"
			optimize "on"
		
		filter "configurations:Dist"
			defines "LM_DIST"
			runtime "Release"
			optimize "on"
