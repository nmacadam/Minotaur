#pragma once
#include "Vertex.h"
#include <vector>
#include <glm/glm.hpp>

class Triangle
{
public:
	std::vector<Vertex> vertices
	{
		//position								//color								//texture (uv)			//normals (we'll calculate these on the fly later)
		Vertex(glm::vec3(0.f,  0.5f, 0.f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f, 0.f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f, 0.f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.0f))
		//Vertex(glm::vec3(0.5f,  -0.5f, 0.f), glm::vec4(0.5f, 0.0f, 0.5f, 1.0f), glm::vec2(1.f, 1.f)),
	};

	//CCW indices!
	std::vector <GLuint> indices
	{  // note that we start from 0!
		0, 1, 2  // first Triangle
	};
};

class Quad
{
public:
	std::vector<Vertex> vertices
	{
		//position								//color								//texture (uv)			//normals (we'll calculate these on the fly later)
		Vertex(glm::vec3(-0.5f,  0.5f, 0.f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  -0.5f, 0.f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f, 0.f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f, 0.f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.0f)),
	};

	std::vector <GLuint> indices // note that we start from 0!
	{
		0, 1, 2,  // first Triangle
		0, 2, 3   // second Triangle
	};
};

class Plane
{
public:
	std::vector<Vertex> vertices
	{
		//position								//color								//texture (uv)			//normals (we'll calculate these on the fly later)
		Vertex(glm::vec3(-0.5f, 0.f, 0.5f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(-0.5f, 0.0f, -0.5f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.f, -0.5f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.f, 0.5f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.0f)),
	};

	std::vector <GLuint> indices
	{
		0, 1, 2,  // first Triangle
		0, 2, 3   // second Triangle
	};
};

class Pyramid
{
public:
	std::vector<Vertex> vertices
	{
		//Position								//Color								//Texcoords				//Normals
		//Triangle front
		Vertex(glm::vec3(0.f, 0.5f, 0.f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.5f, 1.f),	glm::vec3(0.f, 0.f, 1.f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f)),

		//Triangle left
		Vertex(glm::vec3(0.f, 0.5f, 0.f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.5f, 1.f),	glm::vec3(-1.f, 0.f, 0.f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(-1.f, 0.f, 0.f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(-1.f, 0.f, 0.f)),

		//Triangle back
		Vertex(glm::vec3(0.f, 0.5f, 0.f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f)),

		//Triangles right
		Vertex(glm::vec3(0.f, 0.5f, 0.f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f)),
	};
};

class Cube : public Mesh
{
public:
	
	std::vector<Vertex> vertices
	{
		//Position								//Color								//Texcoords				//Normals
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, 1.f)),

		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, -1.f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, -1.f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, -1.f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec4(1.f, 1.0f, 1.0f, 1.0f),	glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, -1.f))
	};

	std::vector <GLuint> indices
	{
		0, 1, 2,
		0, 2, 3,

		7, 6, 1,
		7, 1, 0,

		4, 5, 6,
		4, 6, 7,

		3, 2, 5,
		3, 5, 4
	};
};