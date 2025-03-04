#pragma once
#include "Nova/Renderer/CubeMap.h"
namespace Nova
{
	class OpenGLCubeMap:public CubeMap
	{
	public:
		OpenGLCubeMap(const std::vector<std::string>& faces);
		void Bind(unsigned int solt) override;
		unsigned int GetTextureID() override;
	private:
		unsigned int m_Texture;
		unsigned int loadCubemap(std::vector<std::string> faces);

	};
}


