#pragma once
#include "Component.h"
#include <Vector2.h>

class MoveComponent;
class Actor;

class SeekBehaviour : public Component
{
public:
	SeekBehaviour();
	SeekBehaviour(Actor* target, MoveComponent* moveComponent, float force);
	~SeekBehaviour() {};

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

