project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/**.c"
    }

    filter "system:windows"        
        systemversion "latest"
        defines { "_GLFW_WIN32",  "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
    filter "system:windows"
        
        buildoptions { "-std=c11", "-lgdi32" }
        systemversion "latest"
        staticruntime "On"

        defines { "_GLFW_WIN32",  "_CRT_SECURE_NO_WARNING" }

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
