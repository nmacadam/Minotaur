#version 330 core
out vec4 FragColor;

//struct Material {
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//    vec3 shininess;
//};

//layout (std140) uniform Camera
//{
//    vec3 viewPos;
//};

struct Material {
    sampler2D   diffuse;
    sampler2D   specular;
    float   shininess;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    float constant;
    float linear;
    float quadratic;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    float constant;
    float linear;
    float quadratic;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//in vec3 vertColor;
in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos; 
in vec3 ViewPos;

uniform Material material;
//uniform Light light;
uniform PointLight light;
//uniform DirectionalLight light;

//uniform float time;

uniform vec3 objectColor;
//uniform vec3 viewPos;

void main()
{
    //float distance    = length(light.position - FragPos);
    //float attenuation = 1.0 / (light.constant + light.linear * distance + 
    //		            light.quadratic * (distance * distance));  


    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord));  

    float specularStrength = 0.5;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    


    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;  

    float alpha = texture(material.diffuse, TexCoord).a;
    if (alpha < .01) discard;
    FragColor = vec4(ambient + diffuse + specular, alpha);

    // ambient
    //vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // diffuse
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb; 

    // specular
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize(ViewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //vec3 specular = light.specular * (spec * material.specular); 
    //
    //vec3 result = (ambient + diffuse + specular);// * objectColor;

    //FragColor = vec4(result, 1.0);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(vertColor, 1.0);
} 