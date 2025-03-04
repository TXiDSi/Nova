#pragma once

#include "Nova/Graphic/Mesh.h"
#include "Nova/Component/Transform.h"
#include "Nova/Renderer/Camera.h"
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Nova {

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader,Mesh& model,Transform& transform,Camera& camera);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};


}
