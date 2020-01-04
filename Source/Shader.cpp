#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (!geometryPath.empty())
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if (!geometryPath.empty())
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    if (!geometryPath.empty())
        glAttachShader(programID, geometry);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (!geometryPath.empty())
        glDeleteShader(geometry);


	// Bind uniform block(s)
    GLuint matricesUniformBlockIndex = glGetUniformBlockIndex(programID, "Matrices");
    glUniformBlockBinding(programID, matricesUniformBlockIndex, 0);

    //GLuint cameraUniformBlockIndex = glGetUniformBlockIndex(programID, "Camera");
    //glUniformBlockBinding(programID, cameraUniformBlockIndex, 1);
}

Shader::~Shader()
{
    unuse();
    glDeleteProgram(programID);
}

void Shader::use()
{
	glUseProgram(programID);
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::compileShader(const std::string& path, GLuint id)
{
	/*std::ifstream shaderFile(path);
	if (shaderFile.fail())
	{
		std::cerr << "Shader file could not be opened!\n";
		return;
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line))
	{
		fileContents += line + "\n";
	}

	shaderFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		std::cerr << "Shader failed to compile!\n";
		return;
	}*/
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setVec2f(const std::string& name, glm::fvec2 value)
{
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3f(const std::string& name, glm::fvec3 value)
{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4fv(const std::string& name, glm::mat4 value, GLboolean transpose) const
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, transpose, glm::value_ptr(value));
}

//void Shader::applyMaterial(Material* material)
//{
//    //setInt("material.diffuse", material->diffuseMap->textureUnit);
//    setInt("material.diffuse", 0);
//    material->diffuseMap->bind(0);
//    //setInt("material.specular", material->specularMap->textureUnit);
//    setInt("material.specular", 1);
//    material->specularMap->bind(1);
//}

void Shader::applyCamera(Camera camera)
{
    setVec3f("viewPos", camera.transform->position);
}

// deprecated
//void Shader::applyPointLight(Light light)
//{
//    setVec3f("light.position", light.transform.position);
//	
//    setVec3f("light.ambient", light.ambient);
//    setVec3f("light.diffuse", light.diffuse);
//    setVec3f("light.specular", light.specular);
//}

void Shader::applyDirectionalLight(DirectionalLight light)
{
    setVec3f("light.direction", light.direction);
	
    setVec3f("light.ambient", light.ambient);
    setVec3f("light.diffuse", light.diffuse);
    setVec3f("light.specular", light.specular);
}

void Shader::applyPointLight(PointLight light)
{
    setVec3f("light.position", light.transform->position);
    setFloat("light.constant", light.constant);
    setFloat("light.linear", light.linear);
    setFloat("light.quadratic", light.quadratic);
	
    setVec3f("light.ambient", light.ambient);
    setVec3f("light.diffuse", light.diffuse);
    setVec3f("light.specular", light.specular);
}

void Shader::applySpotLight(SpotLight light)
{
    setVec3f("light.position", light.transform->position);
    setVec3f("light.direction", light.direction);
    setFloat("light.cutOff", light.cutOff);

    setVec3f("light.ambient", light.ambient);
    setVec3f("light.diffuse", light.diffuse);
    setVec3f("light.specular", light.specular);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
