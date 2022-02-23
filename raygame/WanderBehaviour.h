#pragma once
#include "Component.h"
#include <Vector2.h>

class MoveComponent;

class WanderBehaviour : public Component
{
public:
	WanderBehaviour() {};
	WanderBehaviour(MoveComponent* moveComponenet, float force, float radius, float distance);
	~WanderBehaviour() {};

	void update(float deltaTime) override;
private:
	MoveComponent* m_moveComponent;
	MathLibrary::Vector2 m_desiredVelocity;
	MathLibrary::Vector2 m_steeringForce;
	MathLibrary::Vector2 m_currentVelocity;
	float m_force;
	float m_radius;
	float m_circleDistance;
};

