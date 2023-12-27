#pragma once
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Mesh.h"


class SceneObject
{
private:
	Mesh* mesh;
	Shader* shader;

public:
	glm::vec3 position{ 0.f, 0.f, 0.f };
	glm::vec3 rotation{ 0.f, 0.f, 0.f };
	glm::vec3 scale{ 1.f, 1.f, 1.f };

	SceneObject(Mesh* mesh, Shader* sp)
	{
		this->mesh = mesh;
		this->shader = sp;
	}

	void Draw(float x, float y, float z)
	{

			glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
				* glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
				* glm::translate(glm::mat4(1.f), position)
				* glm::scale(glm::mat4(1.f), scale);
			shader->Use();
			shader->SetUniformMat4("model", model);
			shader->SetUniformMat4("scale", glm::scale(glm::mat4(1.f), scale));
			shader->SetUniformFloat("move_x", x);
			shader->SetUniformFloat("move_y", y);
			shader->SetUniformFloat("move_z", z);
	//	}
		mesh->Draw(*shader);
		glUseProgram(0);
	}


};

#endif
