workspace "GameEngine"
    architecture "x64"

    configurations {
        "Debug",
        "Development",
        "Release"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "GameEngine"
    location "GameEngine"
    kind "SharedLib"
    language "C++"

    targetdir("Bins/bin/"..OutputDir.."/%{prj.name}")
    objdir("Bins/Intermediate/"..OutputDir.."/%{prj.name}")

    files {
        "%{prj.name}/Source/Public/**.h",
        "%{prj.name}/Source/Private/**.cpp"
    }

    pchheader "Public/PCH.h"
    pchsource "GameEngine/Source/Private/PCH.cpp"

    includedirs {
        "%{prj.name}/Source",
        "%{prj.name}/ThirdParty/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GameEngine_Platform_Windows",
            "GameEngine_Build_DLL"
        }

        postbuildcommands {
            "{COPY} %{cfg.buildtarget.relpath} ../Bins/bin/"..OutputDir.."/Sandbox"
        }

        buildoptions "/utf-8"

    filter "configurations:Debug"
        defines "GameEngine_Debug"
        symbols "On"

    filter "configurations:Development"
        defines "GameEngine_Development"
        symbols "On"

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "On"

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
        staticruntime "On"
        systemversion "latest"

        defines {
            "GameEngine_Platform_Windows"
        }

        buildoptions "/utf-8"

    filter "configurations:Debug"
        defines "GameEngine_Debug"
        symbols "On"

    filter "configurations:Development"
        defines "GameEngine_Development"
        optimize "On"

    filter "configurations:Release"
        defines "GameEngine_Release"
        optimize "On"