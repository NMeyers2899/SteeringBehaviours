#pragma once
#include "Actor.h"

class FleeBehaviour;
class SeekBehaviour;
class WanderBehaviour;
class MoveComponent;
class SpriteComponent;

class Agent : public Actor
{
public:
	Agent();
	Agent(float xPos, float yPos, Actor* m_target, float fleeForce, float seekForce, 
		float wanderForce);
	~Agent() {};

	void start() override;

	void setTarget(Actor* value);

private:
	Actor* m_target;
	FleeBehaviour* m_fleeBehaviour;
	SeekBehaviour* m_seekBehaviour;
	WanderBehaviour* m_wanderBehaviour;
	MoveComponent* m_moveComponent;
	SpriteComponent* m_spriteComponent;
	float m_fleeForce;
	float m_seekForce;
	float m_wanderForce;
};

