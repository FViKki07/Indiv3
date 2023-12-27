#include "Headers.h"

struct Material
{
	Texture texture;
	GLfloat specular = 0.1f;
	GLfloat shininess = 10.f;
public:
	Material() {}
	Material(const char* texturePath)
	{
		InitializeTexture(texturePath);
	}


	void Use(Shader* s)
	{
		glActiveTexture(GL_TEXTURE0);
		sf::Texture::bind(&texture.texture);

		s->SetUniformFloat("material.specular", specular);
		s->SetUniformFloat("material.shininess", shininess);

	}
private:
	void InitializeTexture(const char* texturePath, std::string type = "texture_diffuse")
	{
		sf::Texture texture1;
		texture1.loadFromFile(texturePath);
		texture1.setRepeated(true);
		texture = { 0, type, texture1 };
	}
};
