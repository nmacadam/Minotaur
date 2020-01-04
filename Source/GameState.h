#pragma once
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include "ECS/ECS.h"

class Engine;

class GameState
{
public:
	GameState() {}
	virtual ~GameState() = default;
	
	//Setup and destroy state
	virtual void Initialize(Engine* game) = 0;
	virtual void Clean() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(Engine* engine) = 0;
	virtual void Update(Engine* engine) = 0;
	virtual void Render(Engine* engine) = 0;


	//template<class Archive>
	//void Serialize(Archive& archive)
	//{
	//	//output = entities.releaseEntities();
	//	archive(CEREAL_NVP(output));
	//}
	
	void ChangeState(Engine* engine, GameState* state);

	EntitySet entities;

	friend class cereal::access;
	
protected:
	
	//GameState() {}
};