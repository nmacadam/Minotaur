#pragma once
#include "ECS.h"

#include "../Shader.h"
#include "../Font.h"

class TextRenderer :
	public Component
{
public:
	TextRenderer(Font* font, Shader* shader) : color(glm::vec3(1,1,1)), scale(1), font(font), shader(shader)
	{}

	void initialize() override;
	void draw() override;

	std::string text = "Test text!";
	
private:
	void RenderText(GLfloat x, GLfloat y);

	Transform* transform;
	
	glm::vec3 color;
	GLfloat scale;

	Font* font;
	Shader* shader;
	GLuint VAO, VBO;
};
