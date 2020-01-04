#pragma once
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	Vertex() = default;

	// todo: reorder!

	Vertex(glm::vec3 Position, glm::vec3 Normal, glm::vec2 UV)
		: position(Position), normal(Normal), uv(UV), tangent(glm::vec3(0.f)), bitangent(glm::vec3(0.f)) {};

	Vertex(glm::vec3 Position, glm::vec3 Color, glm::vec2 UV, glm::vec3 Normal)
		: position(Position), color(Color), normal(Normal), uv(UV), tangent(glm::vec3(0.f)), bitangent(glm::vec3(0.f)) {};
	
	Vertex(glm::vec3 Position, glm::vec3 Normal, glm::vec2 UV, glm::vec3 Tangent, glm::vec3 Bitangent)
		: position(Position), normal(Normal), uv(UV), tangent(Tangent), bitangent(Bitangent) {};

	
	/*Vertex()
		: position(glm::vec3(0.f)), color(glm::vec4(0.f)), uv(glm::vec3(0.f)), normal(glm::vec3(0.f)), tangent(glm::vec3(0.f)), bitangent(glm::vec3(0.f)) {};

	Vertex(glm::vec3 Position, glm::vec4 Color, glm::vec2 UV)
		: position(Position), color(Color), uv(UV), normal(glm::vec3(0.f)), tangent(glm::vec3(0.f)), bitangent(glm::vec3(0.f)) {};
	
	Vertex(glm::vec3 Position, glm::vec4 Color, glm::vec2 UV, glm::vec3 Normal)
		: position(Position), color(Color), uv(UV), normal(Normal), tangent(glm::vec3(0.f)), bitangent(glm::vec3(0.f)) {};
	
	Vertex(glm::vec3 Position, glm::vec4 Color, glm::vec2 UV, glm::vec3 Normal, glm::vec3 Tangent, glm::vec3 Bitangent)
		: position(Position), color(Color), uv(UV), normal(Normal), tangent(Tangent), bitangent(Bitangent) {};
	
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;*/
};