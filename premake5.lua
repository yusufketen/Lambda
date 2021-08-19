workspace "Lambda"
	architecture "x86_64"
	startproject "Lambda-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Lambda/vendor/GLFW/include"
IncludeDir["Glad"] = "Lambda/vendor/Glad/include"
IncludeDir["ImGui"] = "Lambda/vendor/imgui"
IncludeDir["glm"] = "Lambda/vendor/glm"
IncludeDir["stb_image"] = "Lambda/vendor/stb_image"

group "Dependencies"
	include "Lambda/vendor/GLFW"
	include "Lambda/vendor/Glad"
	include "Lambda/vendor/imgui"
group ""

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
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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

			
project "Lambda-Editor"
	location "Lambda-Editor"
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