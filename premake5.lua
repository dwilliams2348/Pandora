workspace "Pandora"
    architecture "x86_64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pandora"
    location "Pandora"
    kind "StaticLib"
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
        "Pandora/src"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PE_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }

        postbuildcommands
        {

        }

    filter "configurations:Debug"
		defines "PE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PE_DIST"
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
        "Pandora/src"
    }

    links
    {
        "Pandora"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PE_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
		defines "PE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PE_DIST"
		optimize "On"