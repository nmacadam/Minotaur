#include "MTime.h"

float MTime::deltaTime = 0.01f;
float MTime::time = 0.f;
float MTime::fps = 0.f;

int MTime::frameCount = 0;
float MTime::startTimer = 0;
float MTime::frameTimer = 0;
int MTime::deltaFPS = 0;