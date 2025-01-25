    
--创建工程
project "imgui"
    kind "StaticLib"
    --设置语言类型
    language "C++"
    --设置配置输出路径
    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    --设置配置中间文件输出路径
    objdir ("bin_int/".. outputdir .. "/%{prj.name}")


    files
    {
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",
		"imgui_tables.cpp",
    }
    
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
               
           
    