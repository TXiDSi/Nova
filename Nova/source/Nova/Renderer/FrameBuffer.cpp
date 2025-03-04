#include "FrameBuffer.h"
#include "NovaPch.h"

#include "Nova/Platform/Opengl/OpenGLFrameBuffer.h"

namespace Nova
{
	std::shared_ptr<FrameBuffer> FrameBuffer::Create()
	{
		return std::make_shared<OpenGLFrameBuffer>();
	}
}
