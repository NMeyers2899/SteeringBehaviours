#pragma once
#include "Actor.h"

class FleeBehaviour;
class SeekBehaviour;
class MoveComponent;
class SpriteComponent;

class Agent : public Actor
{
public:
	Agent();
	Agent(float xPos, float yPos, Actor* m_target);
	~Agent() {};

	void setTarget(Actor* value);

private:
	Actor* m_target;
	FleeBehaviour* m_fleeBehaviour;
	SeekBehaviour* m_seekBehaviour;
	MoveComponent* m_moveComponent;
	SpriteComponent* m_spriteComponent;
};

