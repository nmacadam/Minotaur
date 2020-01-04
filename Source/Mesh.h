#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include "ECS/Transform.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices/*, std::vector<Texture> textures*/);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh();

	void render(Shader* shader);
	void modify(std::vector<Vertex> vertices, std::vector<GLuint> indices/*, std::vector<Texture> textures*/);
	void modify(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();
};

