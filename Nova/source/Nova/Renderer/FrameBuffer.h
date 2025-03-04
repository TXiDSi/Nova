#pragma once
#include <memory>
namespace Nova
{
	class FrameBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual unsigned int GetTextureID() = 0;
		virtual void SetTextureSize(unsigned int width, unsigned int height) = 0;
		static std::shared_ptr<FrameBuffer> Create();
	};
}


