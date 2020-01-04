#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
//out vec3 vertColor;
out vec2 TexCoord;
out vec3 ViewPos;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec3 viewPos;
};

uniform mat4 transform;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

void main()
{
//transform * 
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    //expensive, do on CPU and send to GPU
    Normal = mat3(transpose(inverse(model))) * aNormal;
    //vertColor = aColor;
    TexCoord = aTexCoord;
    ViewPos = viewPos;
}