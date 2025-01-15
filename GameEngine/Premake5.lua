workspace "GameEngine"
    architecture "x64"
	startproject "Sandbox"

    configurations {
        "Debug",
        "Development",
        "Release"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-----------------------------------------------------------------------------------------------------
-- Include the GLFW Premake file to include it as a project
include "GameEngine/ThirdParty/GLFW"
include "GameEngine/ThirdParty/GLAD"
include "GameEngine/ThirdParty/ImGui"

-----------------------------------------------------------------------------------------------------
project "GameEngine"
    location "GameEngine"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
    targetdir("Bins/bin/"..OutputDir.."/%{prj.name}")
    objdir("Bins/Intermediate/"..OutputDir.."/%{prj.name}")

    links{
        "GLFW",
		"GLAD",
		"ImGui",
        "opengl32.lib"
    }

    files {
        "%{prj.name}/Source/Public/**.h",
        "%{prj.name}/Source/Private/**.cpp",
		"%{prj.name}/ThirdParty/GLM/glm/**.hpp",
        "%{prj.name}/ThirdParty/GLM/glm/**.inl"
    }

    pchheader "Public/PCH.h"
    pchsource "GameEngine/Source/Private/PCH.cpp"

    includedirs {
        "%{prj.name}/Source",
        "%{prj.name}/ThirdParty/spdlog/include",
        "%{prj.name}/ThirdParty/GLFW/include",
        "%{prj.name}/ThirdParty/GLAD/include",
        "%{prj.name}/ThirdParty",
        "%{prj.name}/ThirdParty/GLM"
    }

    filter "system:windows"
        systemversion "latest"
		
		buildoptions {"/utf-8"}--, "/wd4251"}

        defines {
            "GameEngine_Platform_Windows",
            "GameEngine_Build_DLL",
			"GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines {"GameEngine_Debug", "GameEngine_AssertsEnabled", "_CRT_SECURE_NO_WARNINGS"}
        symbols "On"
		runtime "Debug"

    filter "configurations:Development"
        defines "GameEngine_Development"
        optimize "On"
		runtime "Release"

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "On"
		symbols "off"
		runtime "Release"

-----------------------------------------------------------------------------------------------------
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
    targetdir("Bins/bin/"..OutputDir.."/%{prj.name}")
    objdir("Bins/Intermediate/"..OutputDir.."/%{prj.name}")

    links {
        "GameEngine"
    }

    files {
        "%{prj.name}/Source/Public/**.h",
        "%{prj.name}/Source/Private/**.cpp",
    }

    includedirs {
        "%{prj.name}/Source",
        "GameEngine/ThirdParty/spdlog/include",
		"GameEngine/ThirdParty",
        "GameEngine/Source",
		"GameEngine/ThirdParty/GLM"
    }

    filter "system:windows"
        systemversion "latest"
		buildoptions {"/utf-8"}--, "/wd4251"}

        defines {
            "GameEngine_Platform_Windows"
			}

    filter "configurations:Debug"
        defines "GameEngine_Debug"
        symbols "on"
		runtime "Debug"

		
    filter "configurations:Development"
        defines "GameEngine_Development"
        optimize "on"
		runtime "Release"

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "on"
		runtime "Release"
        symbols "off"

