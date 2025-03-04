#pragma once
#include "Nova/Renderer/FrameBuffer.h"


namespace Nova
{
	class OpenGLFrameBuffer:public FrameBuffer
	{
	public:
        OpenGLFrameBuffer();
		void Bind() override;
		void UnBind() override;
		unsigned int GetTextureID() override;
		void SetTextureSize(unsigned int width, unsigned int height) override;
	private:
		unsigned int m_Texture;
		unsigned int m_FrameBuffer;
		unsigned int m_RenderBuffer;
        unsigned int m_Width, m_Height;
	};
}


