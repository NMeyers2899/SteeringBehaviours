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
	Agent(float xPos, float yPos, Actor* m_target, float force);
	~Agent() {};

	void start() override;
	void update(float deltaTime) override;
	void onAddComponent(Component* comp) override;

	float getForce() { return m_force; }
	void setForce(float value) { m_force = value; }


	void setTarget(Actor* value);

private:
	Actor* m_target;
	FleeBehaviour* m_fleeBehaviour;
	SeekBehaviour* m_seekBehaviour;
	WanderBehaviour* m_wanderBehaviour;
	MoveComponent* m_moveComponent;
	SpriteComponent* m_spriteComponent;
	float m_force;
	float m_maxSpeed = 200;
};

