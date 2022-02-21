#pragma once
#include "Component.h"
#include <Vector2.h>

class MoveComponent;
class Actor;

class FleeBehaviour : public Component
{
public:
	FleeBehaviour();
	FleeBehaviour(Actor* target, MoveComponent* moveComponent, float force);
	~FleeBehaviour() {};

	void update(float deltaTime) override;

	void setTarget(Actor* value) { m_target = value; }

private:
	Actor* m_target;
	MoveComponent* m_moveComponent;
	MathLibrary::Vector2 m_desiredVelocity;
	MathLibrary::Vector2 m_steeringForce;
	MathLibrary::Vector2 m_currentVelocity;
	float m_force;
};

