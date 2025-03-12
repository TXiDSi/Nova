#pragma once
#include <unordered_map>
#include <Nova/Graphic/Model.h>
namespace Nova
{
	class ResourceManager
	{
	// ---µ¥ÀýÄ£Ê½----------------------------
	public:
		static ResourceManager* GetInstance();
	private:
		static ResourceManager* m_Instance;
		ResourceManager() {}
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
	// --------------------------------------

	public:
		void LoadModel(const std::string& path);
        std::shared_ptr<Model> GetModel(const std::string& path);

		

		std::string GetFileSource(const std::string& path);
		//--------------Shader----------------------------------------------------
		std::string GetVertexShaderSource(const std::string& path);
		std::string GetFragmentShaderSource(const std::string& path);

		void LoadShader(const std::string& path);
		std::shared_ptr<Shader> GetShader(const std::string& path);
		//------------------------------------------------------------------------
	private:
		std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}

