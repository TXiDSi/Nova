#include "novapch.h"
#include "Renderer.h"

#include "Nova/Graphic/Mesh.h"
#include "Nova/Component/Light.h"
#include "Nova/Platform/Opengl/OpenGLShader.h"

namespace Nova {

	std::shared_ptr<Scene> Renderer::m_Scene = nullptr;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader,Mesh& mesh,
		std::shared_ptr<Transform> transform)
	{
		if (m_Scene == nullptr || m_Scene->mainCamera == nullptr || m_Scene->light == nullptr)
			return;

		mesh.Bind();
		shader->Bind();
		shader->SetMat4("view", m_Scene->mainCamera->GetViewMatrix());
		shader->SetMat4("model", transform->GetTransformMatrix());
		shader->SetMat4("projection", m_Scene->mainCamera->GetProjectionMatrix());	
        shader->SetFloat3("lightCol", m_Scene->light->color);
        shader->SetFloat3("lightDir", m_Scene->light->direction);
        //shader->SetFloat3("viewPos", m_Scene->mainCamera->transform.position);
		RenderCommand::DrawElements(mesh.indices.size());		
	}

	void Renderer::BeginScene(std::shared_ptr<Scene> scene)
	{
		m_Scene = scene;
	}

	void Renderer::EndScene()
	{
	}

}