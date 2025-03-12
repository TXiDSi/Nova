#pragma once

#include "Nova/Core/Component.h"
#include "Nova/Graphic/Mesh.h"
#include "Nova/Renderer/Shader.h"

// -> Mesh
// -> Material
namespace Nova
{
	class MeshRenderer: public Component
	{
	public:
		MeshRenderer() = default;

		// Í¨¹ý Component ¼Ì³Ð
		Json::Value ToJson() override;
		void FromJson(const Json::Value& json) override;

		void SetMesh(std::shared_ptr<Mesh> mesh);
		void SetMeshByPath();
		void SetShaderByPath();
		void SetShader(std::shared_ptr<Shader> shader);
		void Update() override;
		void OnImGui() override;

	public:
		std::string modelPath;
		std::string shaderPath;
		int meshIndex;
	private:
		std::shared_ptr<Mesh> m_Mesh = nullptr;
		std::shared_ptr<Shader> m_Shader = nullptr;
	};


}