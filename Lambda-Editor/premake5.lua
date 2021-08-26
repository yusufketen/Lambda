project "Lambda-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Lambda/vendor/spdlog/include",
		"%{wks.location}/Lambda/src",
		"%{wks.location}/Lambda/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
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
