#include "NovaPch.h"
#include "Camera.h"
#include "Nova/Core/GameObject.h"

namespace Nova
{
	Camera::Camera() :m_Fov(glm::radians(45.0f)), m_Aspect(16.0f / 9.0f),
		m_Near(0.1f), m_Far(1000.0f)
	{
		m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
	}
	Camera::~Camera()
	{
	}
	glm::mat4 Camera::GetViewMatrix()
	{
		glm::vec3 position = this->gameObject->transform->position;
		glm::vec3 forward = this->gameObject->transform->GetForward();
		glm::vec3 up = this->gameObject->transform->GetUp();

		return glm::lookAt(position, position + forward, up);
	}
	glm::mat4 Camera::GetProjectionMatrix()
	{
		return m_ProjectionMatrix;
	}
	void Camera::SetProjectionParameters(float fov, float aspect, float nearClip, float farClip)
	{
		m_Fov = fov;
		m_Aspect = aspect;
		m_Near = nearClip;
		m_Far = farClip;
		m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
	}

	Json::Value Camera::ToJson()
	{
		Json::Value root;
        root["fov"] = m_Fov;
        root["aspect"] = m_Aspect;
        root["near"] = m_Near;
        root["far"] = m_Far;
		return root;
	}

	void Camera::FromJson(const Json::Value& json)
	{
        m_Fov = json["fov"].asFloat();
        m_Aspect = json["aspect"].asFloat();
        m_Near = json["near"].asFloat();
        m_Far = json["far"].asFloat();
		m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
	}


}