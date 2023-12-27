#pragma once

#include "Headers.h"
#include "Shader.h"
#include "Material.h"
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};




static std::vector<std::string> split(const std::string& s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		if (item.empty()) continue;
		elems.push_back(item);
	}
	return elems;
}


class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Material* material;
	Texture texture;
	GLuint count;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	void parseFile(const std::string& filePath) {
		try {
			std::ifstream obj(filePath);

			if (!obj.is_open()) {
				throw std::exception("File cannot be opened");
			}

			std::vector<glm::vec3> v;
			std::vector<glm::vec2> vt;
			std::vector<glm::vec3> vn;

			std::vector <std::string> indexAccordance{};
			std::string line;
			while (std::getline(obj, line))
			{
				std::istringstream iss(line);
				std::string type;
				iss >> type;
				if (type == "v") {

					auto vertex = split(line, ' ');
					glm::vec3 cv{};
					for (size_t j = 1; j < vertex.size(); j++)
					{
						cv[j - 1] = std::stof(vertex[j]);
					}
					v.push_back(cv);
				}
				else if (type == "vn") {
					auto normale = split(line, ' ');
					glm::vec3 cv{};
					for (size_t j = 1; j < normale.size(); j++)
					{
						cv[j - 1] = std::stof(normale[j]);
					}
					vn.push_back(cv);
				}
				else if (type == "vt") {
					auto texture = split(line, ' ');
					glm::vec2 cv{};
					for (size_t j = 1; j < 3; j++)
					{
						cv[j - 1] = std::stof(texture[j]);
					}
					vt.push_back(cv);
				}
				else if (type == "f") {
					auto splitted = split(line, ' ');
					auto first = split(splitted[1], '/');
					for (int i = 2; i < splitted.size() - 1; i++)
					{
						auto cur = split(splitted[i], '/');
						auto next = split(splitted[i + 1], '/');

						Vertex vertex0;
						int positionIndex = std::stoi(first[0]) - 1;
						vertex0.Position = glm::vec3(v[positionIndex][0], v[positionIndex][1], v[positionIndex][2]);
						if (first.size() > 1)
						{
							int textureIndex = std::stoi(first[1]) - 1;
							vertex0.TexCoords = glm::vec2(vt[textureIndex][0], vt[textureIndex][1]);
						}
						vertices.push_back(vertex0);
						indices.push_back(indices.size());

						Vertex vertex1;
						positionIndex = std::stoi(cur[0]) - 1;
						vertex1.Position = glm::vec3(v[positionIndex][0], v[positionIndex][1], v[positionIndex][2]);
						if (cur.size() > 1)
						{
							int textureIndex = std::stoi(cur[1]) - 1;
							vertex1.TexCoords = glm::vec2(vt[textureIndex][0], vt[textureIndex][1]);
						}
						vertices.push_back(vertex1);
						indices.push_back(indices.size());

						Vertex vertex2;
						positionIndex = std::stoi(next[0]) - 1;
						vertex2.Position = glm::vec3(v[positionIndex][0], v[positionIndex][1], v[positionIndex][2]);
						if (next.size() > 1)
						{
							int textureIndex = std::stoi(next[1]) - 1;
							vertex2.TexCoords = glm::vec2(vt[textureIndex][0], vt[textureIndex][1]);
						}
						vertices.push_back(vertex2);
						indices.push_back(indices.size());

					}
				}
				else {
					continue;
				}
				
			}
			return;

		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "Vertices loaded: " << vertices.size() << std::endl;
	}

	void InitializeBuffers()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		auto i0 = 0;
		auto i1 = 1;
		auto i2 = 2;

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

		// 3. Устанавливаем указатели на вершинные атрибуты
		// Атрибут с координатами
		glVertexAttribPointer(i0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(i0);
		// Атрибут с нормалями
		glVertexAttribPointer(i1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(i1);
		// Атрибут с текстурными координатами
		glVertexAttribPointer(i2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(i2);

		//Отвязываем VAO
		glBindVertexArray(0);
		glDisableVertexAttribArray(i0);
		glDisableVertexAttribArray(i1);
		glDisableVertexAttribArray(i2);
		//checkOpenGLerror(1);

	}

	/*
	void InitializeTexture(const std::string& texturePath)
	{
		material = new Material(texturePath);
	}*/

public:

	Mesh(const char* objPath, const char* texturePath, GLuint c = 1) {
		count = c;
		parseFile(objPath);
		InitializeBuffers();
		//InitializeTexture(texturePath);
		material = new Material(texturePath);
	}

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures, GLuint c)
	{
		count = c;
		this->vertices = vertices;
		this->indices = indices;
		this->texture = textures[0];

		InitializeBuffers();
	}

	~Mesh() {

	}


	void ReleaseVBO()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}


	virtual void Draw(Shader& shader) const
	{
		shader.Use();
		material->Use(&shader);
		auto unifTexture1 = glGetUniformLocation(shader.ID, "material.diffuse");
		glUniform1i(unifTexture1, 0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		sf::Texture::bind(NULL);
		glUseProgram(0);
	}
};
