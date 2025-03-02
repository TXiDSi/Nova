#include <NovaPch.h>
#include <Nova/Component/Transform.h>

namespace Nova
{
	Transform::Transform():position(glm::vec3(0,0,0)),eulerAngle(glm::vec3(0,0,0))
		,scale(glm::vec3(1,1,1))
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::SetPosition(const glm::vec3& position)
	{
        this->position = position;
	}
	void Transform::SetEulerAngle(const glm::vec3& eulerAngle)
	{
        this->eulerAngle = eulerAngle;
		
	}
	void Transform::SetScale(const glm::vec3& scale)
	{
        this->scale = scale;
	}
	glm::vec3 Transform::GetPosition() const
	{
		return position;
	}
	glm::vec3 Transform::GetEulerAngle() const
	{
		return eulerAngle;
	}
	glm::vec3 Transform::GetScale() const
	{
		return scale;
	}
	glm::mat4 Transform::GetTransformMatrix() const
	{
		glm::mat4 transformMatrix = glm::mat4(1.0f);  // 初始化为单位矩阵
		// z -> y -> x 轴旋转
		transformMatrix = glm::translate(transformMatrix, position);
		transformMatrix = glm::rotate(transformMatrix, glm::radians(eulerAngle.z), glm::vec3(0.0f, 0.0f, 1.0f));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(eulerAngle.y), glm::vec3(0.0f, 1.0f, 0.0f));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(eulerAngle.x), glm::vec3(1.0f, 0.0f, 0.0f));
		transformMatrix = glm::scale(transformMatrix, scale);

		return transformMatrix;
	}

	glm::vec3 Transform::GetForward() const
	{
		glm::vec3 forward;
		forward.x = sin(glm::radians(eulerAngle.y)) * cos(glm::radians(eulerAngle.x));
		forward.y = sin(glm::radians(eulerAngle.x));
		forward.z = cos(glm::radians(eulerAngle.y)) * cos(glm::radians(eulerAngle.x));
		return glm::normalize(forward);
	}

	glm::vec3 Transform::GetRight() const
	{
		glm::vec3 right;
		right.x = cos(glm::radians(eulerAngle.y));
		right.y = 0.0f;
		right.z = sin(glm::radians(eulerAngle.y));
		return glm::normalize(right);
	}

	glm::vec3 Transform::GetUp() const
	{
		return glm::normalize(glm::cross( GetForward(), GetRight()));
	}

} 