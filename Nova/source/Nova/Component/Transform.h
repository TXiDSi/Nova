#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Nova
{
	/*
	* »ù´¡ÊôÐÔ
	* 1.Position
	* 2.Rotation -> Euler Angle|Quaternion
	* 3.Scale
	*/
	class Transform
	{
	public:
        Transform();
        ~Transform();
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