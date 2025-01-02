project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "off"
    
    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files
    {
	    "include/**.h",
        "src/**.c"
    }

    includedirs
    {
        "include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
		buildoptions {"/MDd"}
		
    filter "configurations:Development"
        runtime "Debug"
        symbols "on"
		buildoptions {"/MD"}

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
		buildoptions {"/MD"}