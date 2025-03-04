#pragma once
#include <string>
namespace NovaEditor
{
	class AssetsManager
	{
	public:
		static std::string GetFileSource(const std::string &path);

		//--------------Shader----------------------------------------------------
		static std::string GetVertexShaderSource(const std::string &path);
        static std::string GetFragmentShaderSource(const std::string &path);	
		//------------------------------------------------------------------------

	private:
		static std::string AssetsPath;

	};
}


