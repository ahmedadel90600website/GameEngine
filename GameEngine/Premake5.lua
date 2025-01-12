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
    kind "SharedLib"
    language "C++"

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

    staticruntime "off"

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
		
		buildoptions {"/utf-8", "/wd4251"}

        defines {
            "GameEngine_Platform_Windows",
            "GameEngine_Build_DLL",
			"GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            "{COPY} %{cfg.buildtarget.relpath} ../Bins/bin/"..OutputDir.."/Sandbox"
        }

    filter "configurations:Debug"
        defines {"GameEngine_Debug", "GameEngine_AssertsEnabled"}
        symbols "On"
		runtime "Debug"

    filter "configurations:Development"
        defines "GameEngine_Development"
        symbols "On"
		runtime "Release"

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "On"
		runtime "Release"

-----------------------------------------------------------------------------------------------------
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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

    staticruntime "off"

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
		buildoptions {"/utf-8", "/wd4251"}

        defines {
            "GameEngine_Platform_Windows",
			"IMGUI_API=__declspec(dllimport)"
        }

    filter "configurations:Debug"
        defines "GameEngine_Debug"
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
