#include "HeadBob.h"
#include "../MMath.h"
#include "../../External Libraries/imgui/imgui.h"

void HeadBob::initialize()
{
    if (!entity->hasComponent<Camera>()) entity->addComponent<Camera>();
    camera = &entity->getComponent<Camera>();
}

void HeadBob::update()
{    
    //float horizontal = Input.GetAxis("Horizontal");
   // float vertical = Input.GetAxis("Vertical");

    if (abs(movement.x) == 0 && abs(movement.y) == 0) 
    {
        timer = 0.0f;
    }
    else 
    {
        waveslice = sin(timer);
        timer = timer + bobSpeed;
        if (timer > PI * 2) 
        {
            timer = timer - (PI * 2);
        }
    }
    if (waveslice != 0) 
    {
    	
        float translateChange = waveslice * bobAmount;
        float totalAxes = abs(movement.x) + abs(movement.y);
        totalAxes = glm::clamp(totalAxes, 0.0f, 1.0f);
        translateChange = totalAxes * translateChange;
    	
        camera->transform->position.y = midpoint + translateChange;
    }
    else 
    {
        camera->transform->position.y = midpoint;
    }
}

void HeadBob::draw()
{
}

HeadBob::~HeadBob()
{
}

void HeadBob::drawEditor()
{
    //float p[4] = { position.x, position.y, position.z, position.z };
    ImGui::InputFloat("timer", &timer);
    ImGui::InputFloat("bobspeed", &bobSpeed);
    ImGui::InputFloat("bobamount", &bobAmount);
    ImGui::InputFloat("midpoint", &midpoint);
    ImGui::InputFloat("waveslice", &waveslice);
}