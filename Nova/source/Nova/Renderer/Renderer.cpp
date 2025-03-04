#include "novapch.h"
#include "Renderer.h"

#include "Nova/Graphic/Mesh.h"
#include "Nova/Platform/Opengl/OpenGLShader.h"

namespace Nova {


	void Renderer::Init()
	{
		RenderCommand::Init();
	}



	void Renderer::Submit(const std::shared_ptr<Shader> shader,Mesh& mesh,Transform& transform,Camera& camera)
	{
		mesh.Bind();
		shader->SetMat4("view", camera.GetViewMatrix());
		shader->SetMat4("model", transform.GetTransformMatrix());
		shader->SetMat4("projection", camera.GetProjectionMatrix());
		shader->Bind();
		RenderCommand::DrawElements(mesh.indices.size());		
	}



	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}

}