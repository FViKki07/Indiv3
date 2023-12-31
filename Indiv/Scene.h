#ifndef SCENE_H
#define SCENE_H

#include "Shader.h"
#include "Mesh.h"
#include "SceneObject.h"
#include "Camera.h";


class Scene
{
	Directional_light dir_light;
	sf::Time deltaTime;
	sf::Clock clock;
	sf::Clock unstopClock;
public:
	std::vector<Shader*> shaders;
	std::vector<SceneObject*> sceneObjects;
	Camera camera;

	Scene()
	{
		camera = Camera({ 0.0f, 90.0f, 150.0f });
		dir_light = Directional_light();
	}

	void AddShaderProgram(Shader& sp)
	{
		shaders.push_back(&sp);
	}

	void AddSceneObject(SceneObject& so)
	{
		sceneObjects.push_back(&so);
	}

	void Draw(float move_x, float move_y, float move_z)
	{
	
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 1000.0f);

		for (auto& shader : shaders)
		{
			shader->Use();
			shader->SetUniformFloat("TIME", unstopClock.getElapsedTime().asSeconds());
			shader->SetUniformVec3("viewPos", camera.Position);
			shader->SetUniformMat4("projection", projection);
			shader->SetUniformMat4("view", camera.GetViewMatrix());

			shader->SetUniformVec3("directionalLight.direction", dir_light.direction);
			shader->SetUniformVec3("directionalLight.ambient", dir_light.ambient);
			shader->SetUniformVec3("directionalLight.diffuse", dir_light.diffuse);
			shader->SetUniformVec3("directionalLight.specular", dir_light.specular);

			glUseProgram(0);
		}

		for (auto& sceneObject : sceneObjects)
		{
			//sceneObject->rotation.y = rotationAngle;
			sceneObject->Draw(move_x,move_y,move_z);
		}
	}

	float getDeltaTime()
	{
		return deltaTime.asSeconds();
	}

private:
	std::vector<Mesh> meshes;
};


#endif
