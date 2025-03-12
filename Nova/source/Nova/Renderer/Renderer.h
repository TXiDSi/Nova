#pragma once
#include "Nova/Core/Scene.h"
#include "Nova/Graphic/Mesh.h"
#include "Nova/Component/Transform.h"
#include "Nova/Component/Camera.h"
#include "RenderCommand.h"

#include "Shader.h"

namespace Nova {

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(std::shared_ptr<Scene> scene);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader,
			Mesh& mesh, std::shared_ptr<Transform> transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static std::shared_ptr<Scene> m_Scene;
	};


}
