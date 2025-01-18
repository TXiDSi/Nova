workspace "Nova"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Nova"
    location "Nova"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin_int/".. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }
    
    includedirs
    {
        "%{prj.name}/external/spdlog/include"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "IS_NOVA_BUILD"
        }
    
    
   filter "action:vs*"
      buildoptions { "/utf-8" }  -- 设置 UTF-8 编码
      
   postbuildcommands
   {
        ("{COPY} %{cfg.buildtarget.relpath}../bin/" ..outputdir.."/NovaEditor")
   }
   
    
    filter "configurations:Debug"
        defines "IS_NOVA_DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "IS_NOVA_RELEASE"
        optimize "On"
        
project "NovaEditor"
    location "NovaEditor"
    kind "ConsoleApp"
    language "C++"
    
    
    targetdir ("bin/".. outputdir .. "/%{prj.name}")
        objdir ("bin_int/".. outputdir .. "/%{prj.name}")
        
        files
        {
            "%{prj.name}/source/**.h",
            "%{prj.name}/source/**.cpp"
        }
        
        includedirs
        {
            "Nova/external/spdlog/include",
            "Nova/source"
        }
   filter "action:vs*"
      buildoptions { "/utf-8" }  -- 设置 UTF-8 编码
        
        links
        {
            "Nova"
        }
        
        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"
            
        filter "configurations:Debug"
            defines "IS_NOVA_DEBUG"
            symbols "On"
        filter "configurations:Release"
            defines "IS_NOVA_RELEASE"
            optimize "On"            
           
    