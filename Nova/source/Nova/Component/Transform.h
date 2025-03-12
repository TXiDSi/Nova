#pragma once
#include "Nova/Core/Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Nova
{
	/*
	* 基础属性
	* 1.Position
	* 2.Rotation -> Euler Angle|Quaternion
	* 3.Scale
	*/
	class Transform : public Component
	{

	public:
		void OnImGui() override;
	public:
        Transform();
        ~Transform();

		// 通过 Component 继承
		Json::Value ToJson() override;
		void FromJson(const Json::Value& json) override;

        void SetPosition(const glm::vec3& position);
		void SetEulerAngle(const glm::vec3& eulerAngle);
		void SetScale(const glm::vec3& scale);

        glm::vec3 GetPosition() const;
        glm::vec3 GetEulerAngle() const;
        glm::vec3 GetScale() const;

		glm::mat4 GetRotationMatrix();
		glm::mat4 GetTransformMatrix() const;

		glm::vec3 GetForward() const;
		glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;
	public:
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 eulerAngle;


	};
}