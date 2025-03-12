#include "NovaPch.h"
#include "Nova/Core/Log.h"
#include "Nova/Core/GameObject.h"
#include "Nova/Renderer/Renderer.h"
#include "MeshRenderer.h"
#include "Nova/Core/ResourceManager.h"

namespace Nova
{
	void MeshRenderer::SetMesh(std::shared_ptr<Mesh> mesh)
	{
        m_Mesh = mesh;
	}
	void MeshRenderer::SetMeshByPath()
	{
        auto model = ResourceManager::GetInstance()->GetModel(modelPath);
        if (model)
        {
			if (model->meshes.size() > meshIndex)
			{
				m_Mesh = model->meshes[meshIndex];
			}
			else
			{
                NOVA_CORE_ERROR("MeshRenderer::SetMeshByPath() - Mesh index out of range!");
			}
        }
		else
		{
			NOVA_CORE_ERROR("MeshRenderer::SetMeshByPath() - Model not found!");
		}
	}
	void MeshRenderer::SetShaderByPath()
	{
		auto shader = ResourceManager::GetInstance()->GetShader(shaderPath);
        if (shader)
        {
            m_Shader = shader;
        }
		else
		{
			NOVA_CORE_ERROR("MeshRenderer::SetShaderByPath() - Shader not found!");
		}
	}
	void MeshRenderer::SetShader(std::shared_ptr<Shader> shader)
	{
        m_Shader = shader;
	}
	void MeshRenderer::Update()
	{
		if (m_Shader == nullptr || m_Mesh == nullptr)
		{
			return;
		}
        Renderer::Submit(m_Shader, *m_Mesh, this->gameObject->transform);
	}

	void MeshRenderer::OnImGui()
	{
		ImGui::Text("MeshRenderer");

		ImGui::Text("ModelPath:");
		ImGui::SameLine();
		char buffer[256];
		strncpy(buffer, modelPath.c_str(), sizeof(buffer));
		buffer[sizeof(buffer) - 1] = '\0';
		if (ImGui::InputText("##ModelPath", buffer, sizeof(buffer)))
		{
			modelPath = std::string(buffer);
		}

		ImGui::Text("MeshIndex:");
        ImGui::SameLine();
        ImGui::InputInt("##MeshIndex", &meshIndex);

		if (ImGui::Button("Load Model"))
		{
			SetMeshByPath();
		}

		ImGui::Text("ShaderPath:");
        ImGui::SameLine();
		char buffer2[256];
        strncpy(buffer2, shaderPath.c_str(), sizeof(buffer2));
        buffer2[sizeof(buffer2) - 1] = '\0';
        if (ImGui::InputText("##ShaderPath", buffer2, sizeof(buffer2)))
		{
			shaderPath = std::string(buffer2);
		}

		if (ImGui::Button("Load Shader"))
		{
            SetShaderByPath();
		}
	}
	Json::Value MeshRenderer::ToJson()
	{
		Json::Value root;
        root["modelPath"] = modelPath;
        root["meshIndex"] = meshIndex;
        root["shaderPath"] = shaderPath;
		return root;

	}
	void MeshRenderer::FromJson(const Json::Value& json)
	{
        modelPath = json["modelPath"].asString();
        meshIndex = json["meshIndex"].asInt();
        shaderPath = json["shaderPath"].asString();
		SetMeshByPath();
        SetShaderByPath();
	}
}

