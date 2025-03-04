#include "AssetsManager.h"

#include "Nova/Core/Log.h"
using namespace Nova;

#include <iostream>
#include <fstream>
#include <sstream>



namespace NovaEditor
{
	std::string AssetsManager::AssetsPath = "E:/Nova/Assets/";


	std::string AssetsManager::GetFileSource(const std::string& path)
	{
		std::string fullPath = AssetsPath + path;
		std::ifstream file(fullPath);
		if (!file.is_open())
		{
			NOVA_CORE_ASSERT(false, "Could not open file: " + fullPath);
			return std::string();
		}

		std::stringstream buffer;
        buffer << file.rdbuf();
		std::string source = buffer.str();
        file.close();
        return source;
	}

	std::string AssetsManager::GetVertexShaderSource(const std::string& path)
	{
        std::string fileSource = GetFileSource(path);
		size_t shaderStart = fileSource.find("#VertexBegin");
		if (shaderStart == std::string::npos)
		{
            NOVA_CORE_ASSERT(false, "Could not find #VertexBegin in shader file: " + path);
            return std::string();
		}
		shaderStart+=strlen("#VertexBegin");
        size_t shaderEnd = fileSource.find("#VertexEnd");
        if (shaderEnd == std::string::npos)
        {
            NOVA_CORE_ASSERT(false, "Could not find #VertexEnd in shader file: " + path);
            return std::string();
        }
        return fileSource.substr(shaderStart, shaderEnd - shaderStart);
	}
	std::string AssetsManager::GetFragmentShaderSource(const std::string& path)
	{
        std::string fileSource = GetFileSource(path);
        size_t shaderStart = fileSource.find("#FragmentBegin");
        if (shaderStart == std::string::npos)
        {
            NOVA_CORE_ASSERT(false, "Could not find #FragmentBegin in shader file: " + path);
            return std::string();
        }
        shaderStart+=strlen("#FragmentBegin");
        size_t shaderEnd = fileSource.find("#FragmentEnd");
        if (shaderEnd == std::string::npos)
        {
            NOVA_CORE_ASSERT(false, "Could not find #FragmentEnd in shader file: " + path);
            return std::string();
        }
        return fileSource.substr(shaderStart, shaderEnd - shaderStart);
		
	}

}