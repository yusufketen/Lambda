workspace "Lambda"
	architecture "x64"

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

include "Lambda/vendor/GLFW"

project "Lambda"
	location "Lambda"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLFW}"
	}

	links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LM_PLATFORM_WINDOWS",
			"LM_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "LM_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "LM_RELEASE"
			buildoptions "/MD"
			optimize "On"
		
		filter "configurations:Dist"
			defines "LM_DIST"
			buildoptions "/MD"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LM_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "LM_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "LM_RELEASE"
			buildoptions "/MD"
			optimize "On"
		
		filter "configurations:Dist"
			defines "LM_DIST"
			buildoptions "/MD"
			optimize "On"