#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/fwd.hpp>

#include "ECS/Light.h"
#include "ECS/Camera.h"
//#include "Material.h"

class Material;

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = std::string());
	~Shader();
	
	void use();
	void unuse();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setVec2f(const std::string& name, glm::fvec2 value);
	void setVec3f(const std::string& name, glm::fvec3 value);
	void setMat4fv(const std::string& name, glm::mat4 value, GLboolean transpose = GL_FALSE) const;

	//void applyMaterial(Material* material);
	void applyCamera(Camera camera);
	//void applyPointLight(Light light);
	void applyDirectionalLight(DirectionalLight light);
	void applyPointLight(PointLight light);
	void applySpotLight(SpotLight light);

	GLuint getID() { return programID;  }

private:
	void checkCompileErrors(GLuint shader, std::string type);
	void compileShader(const std::string& path, GLuint id);
	
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	GLuint geometryShaderID;
};
