#include "DeveloperState.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Source/Engine.h"
#include "Source/Mesh.h"
#include "Source/Primitives.h"
#include "Source/Model.h"
#include "Source/ECS/Camera.h"
#include <SDL.h>
#include "Source/ECS/MeshRenderer.h"
#include "Source/TextureCache.h"
#include "Source/Shader.h"

#include "Source/Game/PlayerController.h"
#include "Source/ECS/BoxCollider.h"
#include "Source/ResourceManager.h"
#include "Source/Debug.h"

#include <fstream>
#include "Source/ECS/TextRenderer.h"
#include "Source/MTime.h"
#include "Source/ECS/FPSCounter.h"

//PointLight light(
//    Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1)),
//    glm::vec3(0.9f), 
//    glm::vec3(0.2f, 0.2f, 0.2f), 
//    glm::vec3(0.5f, 0.5f, 0.5f), 
//    glm::vec3(1.0f, 1.0f, 1.0f)
//);

//Camera camera;

Shader* shader = nullptr;
Shader* lampShader = nullptr;
Shader* textShader = nullptr;

ResourceManager Resources;
TextureCache tcache;

Texture* monster = nullptr;
Texture* questionMap = nullptr;
Texture* questionMap2 = nullptr;
Texture* floormap = nullptr;

Texture* diffuseMap;
Texture* specularMap;

Material* material1 = nullptr;
Material* material2 = nullptr;
Material* floormaterial = nullptr;
Material* lampMaterial = nullptr;

Font* font;

Model* loadedmodel = nullptr;

Cube cube;
Quad quad;
Plane plane;

Mesh* mesh = nullptr;
Mesh* q_mesh = nullptr;
Mesh* p_mesh = nullptr;

Transform t(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

int map[24][24] =
{
    {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,0,0,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,0,0,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
    {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
    {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
    {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
    {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
    {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
    {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

PointLight light(
    1.0f,
    0.09f,
    0.032f,
    glm::vec3(.9f),
    glm::vec3(0.2f, 0.2f, 0.2f), 
    glm::vec3(0.5f, 0.5f, 0.5f), 
    glm::vec3(1.0f, 1.0f, 1.0f)
);

void DeveloperState::Initialize(Engine* game)
{
    Engine::loadedEntities = &entities;
	
    lampShader = new Shader("./Shaders/vertex.glsl", "./Shaders/lampf.glsl");
    shader = new Shader("./Shaders/vertex.glsl", "./Shaders/fragment.glsl");
    textShader = new Shader("./Shaders/text_v.glsl", "./Shaders/text_f.glsl");

    monster = Resources.Textures.Load("./Resources/eyeBoy1.png", GL_TEXTURE_2D);
    monster->textureUnit = 0;
	
    questionMap = Resources.Textures.Load("./Resources/container.png", GL_TEXTURE_2D);
    floormap = Resources.Textures.Load("./Resources/StoneWall8.png", GL_TEXTURE_2D);
    questionMap->textureUnit = 0;
    questionMap2 = Resources.Textures.Load("./Resources/container_specular.png", GL_TEXTURE_2D);
    questionMap2->textureUnit = 1;
	
    material1 = new Material(monster, questionMap2, shader);
    material2 = new Material(questionMap, questionMap2, shader);
    floormaterial = new Material(floormap, questionMap2, shader);
    lampMaterial = new Material(lampShader);

    font = Resources.Fonts.Load("./Resources/Roboto-Medium.ttf");
	
    mesh = new Mesh(cube.vertices, cube.indices);
    q_mesh = new Mesh(quad.vertices, quad.indices);
    p_mesh = new Mesh(plane.vertices, plane.indices);

    auto& e1(entities.addEntity());
    e1.name = "Player";
    e1.addComponent<Transform>(t);
    e1.addComponent<Camera>();
    e1.addComponent<HeadBob>();
    e1.addComponent<PlayerController>(5.f);
    e1.addComponent<BoxCollider>(glm::vec3(.5f), glm::vec3(0, .5, 0));
	
    light.transform = &e1.getComponent<Transform>();
    shader->use();
	
    auto& t1 = entities.addEntity();
    t1.name = "Text";
    t1.addComponent<Transform>(glm::vec3(0), glm::vec3(0), glm::vec3(1));
    t1.addComponent<TextRenderer>(font, textShader);
    t1.addComponent<FPSCounter>();

    for (unsigned int i = 0; i < 24; i++)
    {
        for (unsigned int j = 0; j < 24; j++)
        {
            if (map[i][j] < 1) continue;

            auto& e = entities.addEntity();
            e.name = "[" + std::to_string(i) + "]" + "[" + std::to_string(j) + "]";
            e.addComponent<Transform>(glm::vec3(i, 0.5f, j), glm::vec3(0), glm::vec3(1));
            e.addComponent<MeshRenderer>(mesh, material2);
        }
    }

    auto& floor = entities.addEntity();
    floor.name = "Floor";
    floor.addComponent<Transform>(glm::vec3(0), glm::vec3(0), glm::vec3(20, 1, 20));

    auto& e2 = entities.addEntity();
    e2.name = "Monster";
    e2.addComponent<Transform>(glm::vec3(3, 10, 3), glm::vec3(0), glm::vec3(1));
    e2.addComponent<MeshRenderer>(q_mesh, material1);

    //loadedmodel = Resources.Models.Load("./Resources/Lavender.obj");
}

void DeveloperState::Clean()
{
    delete lampShader;
    delete shader;
    delete textShader;

    delete material1;
    delete material2;
    delete floormaterial;
    delete lampMaterial;

    delete mesh;
    delete q_mesh;
    delete p_mesh;
}          

void DeveloperState::Pause()
{
}

void DeveloperState::Resume()
{
}

void DeveloperState::HandleEvents(Engine* game)
{
}

void DeveloperState::Update(Engine* game)
{
	entities.update();
}

void DeveloperState::Render(Engine* game)
{
    shader->applyPointLight(light);
    entities.draw();
}
