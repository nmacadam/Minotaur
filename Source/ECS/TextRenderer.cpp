#include "TextRenderer.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Engine.h"

void TextRenderer::initialize()
{
	if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();
	
	// Generate VAO and VBO for glyph textures
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// We'll be updating the VBO often so we'll use dynamic draw mode
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::draw()
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Engine::SCREEN_WIDTH), 0.0f, static_cast<GLfloat>(Engine::SCREEN_HEIGHT));
	shader->use();
	shader->setMat4fv("projection", projection);

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, transform->position);
	model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	shader->setMat4fv("model", model);
	
	RenderText(0.0f, 0.0f);
}

void TextRenderer::RenderText(GLfloat x, GLfloat y)
{
	//std::cout << "rendering text\n" << std::endl;

	// Activate corresponding render state	
	shader->use();
	glUniform3f(glGetUniformLocation(shader->getID(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Glyph ch = font->getGlyph(*c);

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6)* scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
