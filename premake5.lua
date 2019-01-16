workspace "ClipEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}";

project "Clip"
    location "Clip"
    kind "SharedLib"
    language "C++"

    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    includedirs "%{prj.name}/src"

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CL_PLATFORM_WINDOWS",
            "CL_BUILD_DLL"
        }

        postbuildcommands
        {
            ( "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox" )
        }

    filter "configurations:Debug"
        defines "CL_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "CL_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "CL_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "Clip/src"
    }

    links
    {
        "Clip"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CL_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CL_DEBUG"
        buildoptions "/MTd"
        symbols "On"

    filter "configurations:Release"
        defines "CL_RELEASE"
        buildoptions "/MT"
        optimize "On"

    filter "configurations:Dist"
        defines "CL_DIST"
        buildoptions "/MT"
        optimize "On"