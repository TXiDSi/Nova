    
--创建工程
project "Glad"
    kind "StaticLib"
    --设置语言类型
    language "C"
    staticruntime "on"
    --设置配置输出路径
    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    --设置配置中间文件输出路径
    objdir ("bin_int/".. outputdir .. "/%{prj.name}")


    files
    {
        "include/glad.glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }
    --设置配置头文件搜索路径
    includedirs
    {
        "include"
    }
    
    filter "system:windows"
        
        systemversion "latest"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
               
           
    