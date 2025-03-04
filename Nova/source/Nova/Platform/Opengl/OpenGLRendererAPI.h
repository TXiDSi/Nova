#pragma once

#include "Nova/Renderer/RendererAPI.h"

namespace Nova {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawElements(unsigned int count) override;
	};


}
