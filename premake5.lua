include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Lambda"
	architecture "x86_64"
	startproject "Lambda-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Glad"] = "%{wks.location}/Lambda/vendor/Glad/include"
IncludeDir["GLFW"] = "%{wks.location}/Lambda/vendor/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/Lambda/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Lambda/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Lambda/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Lambda/vendor/entt/include"

group "Dependencies"
	include "vendor/premake"
	include "Lambda/vendor/Glad"
	include "Lambda/vendor/GLFW"
	include "Lambda/vendor/imgui"
group ""

include "Lambda"
include "Sandbox"
include "Lambda-Editor"
