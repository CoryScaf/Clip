workspace "ClipEngine"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Clip-Core"
    kind "StaticLib"
    language "C"

    targetdir( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir( "bin-int/" .. outputdir .. "/%{prj.name}" )

    pchheader "pch.h"
    pchsource "%{prj.name}/pch.c"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c",
        "%{prj.name}/pch.h",
        "%{prj.name}/pch.c"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/",
        "%VULKAN_SDK%/include"
    }

    filter "system:linux"
        libdirs{ os.findlib( "X11" ) }

    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "CP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CP_DIST"
        optimize "On"

project "Clip"
    kind "SharedLib"
    language "C++"

    targetdir( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir( "bin-int/" .. outputdir .. "/%{prj.name}" )

    pchheader "pch.hpp"
    pchsource "%{prj.name}/pch.cpp"

    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/pch.hpp",
        "%{prj.name}/pch.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/",
        "Clip-Core/src",
        "%VULKAN_SDK%/include"
    }
    
    links {"Clip-Core"}
    
    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CP_DIST"
        optimize "On"

project "Sandbox"
    kind "WindowedApp"
    language "C++"

    targetdir( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir( "bin-int/" .. outputdir .. "/%{prj.name}" )

    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Clip/src",
        "Clip-Core/src"
    }

    links
    {
        "Clip",
        "Clip-Core"
    }

    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CP_DIST"
        optimize "On"
