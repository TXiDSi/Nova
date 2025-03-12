#include "NovaPch.h"
#include "ResourceManager.h"
#include "Nova/Core/Log.h"

#include "iostream"
#include "fstream"

namespace Nova
{
	// ---µ¥ÀýÄ£Ê½----------------------------
	ResourceManager* ResourceManager::m_Instance = nullptr;
	ResourceManager* ResourceManager::GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new ResourceManager();
		}
		return m_Instance;
	}
	// --------------------------------------
	void ResourceManager::LoadModel(const std::string& path)
	{
        m_Models[path] = std::make_shared<Model>(path);
	}
    std::shared_ptr<Model> ResourceManager::GetModel(const std::string& path)
    {
        if (m_Models.find(path) == m_Models.end())
        {
            LoadModel(path);
        }
        return m_Models[path];
    }
	void ResourceManager::LoadShader(const std::string& path)
	{
        if (m_Shaders.find(path) != m_Shaders.end())
            return;
        auto vertexSrc = GetVertexShaderSource(path);
        auto fragmentSrc = GetFragmentShaderSource(path);
        m_Shaders[path] = Shader::Create(vertexSrc, fragmentSrc);
	}
	std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& path)
	{
        if (m_Shaders.find(path) == m_Shaders.end())
            LoadShader(path);
        return m_Shaders[path];
	}

    std::string ResourceManager::GetFileSource(const std::string& path)
    {
        std::string fullPath = path;
        std::ifstream file(fullPath);
        if (!file.is_open())
        {
            NOVA_CORE_ERROR("Could not open file: " + fullPath);
            return std::string();
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
        file.close();
        return source;
    }

    std::string ResourceManager::GetVertexShaderSource(const std::string& path)
    {
        std::string fileSource = GetFileSource(path);
        size_t shaderStart = fileSource.find("#VertexBegin");
        if (shaderStart == std::string::npos)
        {
            NOVA_CORE_ERROR("Could not find #VertexBegin in shader file: " + path);
            return std::string();
        }
        shaderStart += strlen("#VertexBegin");
        size_t shaderEnd = fileSource.find("#VertexEnd");
        if (shaderEnd == std::string::npos)
        {
            NOVA_CORE_ERROR("Could not find #VertexEnd in shader file: " + path);
            return std::string();
        }
        return fileSource.substr(shaderStart, shaderEnd - shaderStart);
    }
    std::string ResourceManager::GetFragmentShaderSource(const std::string& path)
    {
        std::string fileSource = GetFileSource(path);
        size_t shaderStart = fileSource.find("#FragmentBegin");
        if (shaderStart == std::string::npos)
        {
            NOVA_CORE_ERROR("Could not find #FragmentBegin in shader file: " + path);
            return std::string();
        }
        shaderStart += strlen("#FragmentBegin");
        size_t shaderEnd = fileSource.find("#FragmentEnd");
        if (shaderEnd == std::string::npos)
        {
            NOVA_CORE_ERROR("Could not find #FragmentEnd in shader file: " + path);
            return std::string();
        }
        return fileSource.substr(shaderStart, shaderEnd - shaderStart);

    }
}

