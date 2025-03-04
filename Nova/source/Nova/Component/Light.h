#pragma once
#include "glm/glm.hpp"

namespace Nova
{
	class Light
	{
	public:
		glm::vec3 color;
	};

	class DirectionalLight : public Light
	{
	public:
		glm::vec3 direction;
	};
}