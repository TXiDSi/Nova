--工作空间 相当于定义域
workspace "Nova"
--architecture:结构
    architecture "x64"
--configuration:配置
    configurations
    {
        "Debug",
        "Release"
    }

--凡是含有配置描述的指的是在VS中通过项目设置的内容，并非premake5输出的配置

--以下是比较常见的
--cfg.name 当前配置的名称 Debug、Release
--cfg.buildtarget 获取或者设置构建目标的文件路径
--cfg.platform 当前配置的平台 x86 x64
--cfg.targetdir 当前配置的输出目录
--cfg.objdir 中间文件的输出目录
--cfg.kind 构建目标的类型 ConsoleApp WindowedApp StaticLib SharedLib
--cfg.symbols 是否开启调试 On Off Auto
--cfg.files 获取所有源文件
--cfg.targetname 构建目标的名称
--cfg.toolset 当前配置的工具链的名称
--cfg.system 当前配置的系统类型 Windows Linux macOS
--cfg.linkoptions 获取或者设置链接选项
--定义输出路径
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Nova/external/glad"

--创建工程
project "Nova"
    --设置构建文件存放路径 默认是相对路径 可以写绝对路径
    location "Nova"
    --构建目标的类型 SharedLib对应动态库 StaticLib对应静态库 
    --ConsoleApp对应可执行文件 WindowedApp对应窗口程序
    kind "SharedLib"
    --设置语言类型
    language "C++"
    --设置配置输出路径
    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    --设置配置中间文件输出路径
    objdir ("bin_int/".. outputdir .. "/%{prj.name}")
    --设置需要编译的文件
    --**.h表示当前目录下所有h文件 以此类推
    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }
    --设置配置头文件搜索路径
    includedirs
    {
        --包含spd，方便DEBUG
        "%{prj.name}/external/spdlog/include",
        --包含source，便利文件耦合调用
        "%{prj.name}/source",
        --包含GLFW
        "%{prj.name}/external/glfw-3.4/include",
        --包含glad
        "%{prj.name}/external/glad/include"
    }
    --链接库存放位置
    libdirs
    {
        --glfw库文件位置
        "%{prj.name}/external/glfw-3.4/lib"
        
    }
    --链接库
    links
    {
        --glfw库文件名称 会自动加上lib
        "glfw3dll",
        "glad"
    }
    
    --project下的大部分配置都是全局的
    --filter可以让你用特定的构建配置 类似如下
    --configurations:Debug|Release
    --platforms:x86|x64
    --action:vs2022|gmake|vs*
    --kind:ConsoleApp|WindowedApp|SharedLib|StaticLib
    --system:windows|linux|macOS
    filter "system:windows"
        --CPP编译标准设置
        cppdialect "C++17"
        --是否开启静态链接
        staticruntime "On"
        --目标操作系统版本 可以latest使用最新的
        systemversion "latest"
        --预定义宏
        defines
        {
            "IS_NOVA_BUILD"
        }
    
   --末尾的* 表示任意vs版本 
   filter "action:vs*"
      --构建编译选项 本质上就是命令行
      buildoptions { 
      -- 设置 UTF-8 编码
      "/utf-8",
      -- 设置运行库为 MD
      "/MD"
       }  
   
   --构建后处理命令 这里是拷贝 常见的有 
   --{COPY} 源路径 目标路径
   --{MKDIR} 目录路径
   --{MOVE} 源路径 目标路径
   --{DELETE} 文件或目录路径
   --{RENAME} 源路径 目标路径
   --中间空格隔开就可以了
   postbuildcommands
   {
        --提前创建对应的文件夹避免出错
        ("{MKDIR} ../bin/"..outputdir.."/NovaEditor"),
        --COPY对应dll到Editor执行文件处
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/NovaEditor")
   }
   --到此已经基本介绍完了大部分基础内容 剩下内容自行理解即可
    
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
        
        libdirs
        {
            "Nova/external/glfw-3.4/lib"
        }
   filter "action:vs*"
        buildoptions { 
            -- 设置 UTF-8 编码
            "/utf-8",
            -- 设置运行库为 MD
            "/MD"
             }
        
        links
        {
            "Nova",
            "glfw3dll"
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
           
    