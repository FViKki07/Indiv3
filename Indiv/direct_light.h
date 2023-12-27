#pragma once
#include "Headers.h"

struct Directional_light
{
	glm::vec3 direction = { -0.0f, -1.0f, -0.0f};

	glm::vec3 ambient = { 0.2f, 0.2f, 0.2f };
	glm::vec3 diffuse = { 1.0f, 1.0f, 0.95f };
	glm::vec3 specular = { 1.0f, 1.0f, 0.95f };

	Directional_light() {};
};