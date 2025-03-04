#pragma once
#include "memory"
#include "vector"
#include "string"
namespace Nova
{
	class CubeMap
	{
	public:
		virtual void Bind(unsigned int solt) = 0;
		virtual unsigned int GetTextureID() = 0;
		static std::shared_ptr<CubeMap> Create(const std::vector<std::string> &faces);	
	};
}


