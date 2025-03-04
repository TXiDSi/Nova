#pragma once

#include "RendererAPI.h"

namespace Nova {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

        inline static void DrawElements(unsigned int count)
		{
			s_RendererAPI->DrawElements(count);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}