#include "GameState.h"
#include "Engine.h"

void GameState::ChangeState(Engine* engine, GameState* state)
{
	engine->changeState(state);
}