workspace "GameEngine"
    architecture "x64"

    configurations {
        "Debug",
        "Development",
        "Release"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-----------------------------------------------------------------------------------------------------
-- Include the GLFW Premake file to include it as a project
include "GameEngine/ThirdParty/GLFW"

-----------------------------------------------------------------------------------------------------
project "GameEngine"
    location "GameEngine"
    kind "SharedLib"
    language "C++"

    targetdir("Bins/bin/"..OutputDir.."/%{prj.name}")
    objdir("Bins/Intermediate/"..OutputDir.."/%{prj.name}")

    links{
        "GLFW",
        "opengl32.lib"
    }

    files {
        "%{prj.name}/Source/Public/**.h",
        "%{prj.name}/Source/Private/**.cpp"
    }

    pchheader "Public/PCH.h"
    pchsource "GameEngine/Source/Private/PCH.cpp"

    includedirs {
        "%{prj.name}/Source",
        "%{prj.name}/ThirdParty/spdlog/include",
        "%{prj.name}/ThirdParty/GLFW/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        --staticruntime "On"
        systemversion "latest"
		
		buildoptions {"/utf-8", "/wd4251"}

        defines {
            "GameEngine_Platform_Windows",
            "GameEngine_Build_DLL"
        }

        postbuildcommands {
            "{COPY} %{cfg.buildtarget.relpath} ../Bins/bin/"..OutputDir.."/Sandbox"
        }

    filter "configurations:Debug"
        defines {"GameEngine_Debug", "GameEngine_AssertsEnabled"}
        symbols "On"
		buildoptions {"/MDd"}

    filter "configurations:Development"
        defines "GameEngine_Development"
        symbols "On"
		buildoptions {"/MD"}

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "On"
		buildoptions {"/MD"}

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
        "%{prj.name}/Source/Private/**.cpp"
    }

    includedirs {
        "%{prj.name}/Source",
        "GameEngine/ThirdParty/spdlog/include",
        "GameEngine/Source"
    }

    filter "system:windows"
        cppdialect "C++17"
        --staticruntime "On"
        systemversion "latest"
		buildoptions {"/utf-8", "/wd4251"}

        defines {
            "GameEngine_Platform_Windows"
        }

    filter "configurations:Debug"
        defines "GameEngine_Debug"
        symbols "On"
		buildoptions {"/MDd"}

		
    filter "configurations:Development"
        defines "GameEngine_Development"
        optimize "On"
		buildoptions {"/MD"}

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "On"
        symbols "off"
		buildoptions {"/MD"}