#include "WanderBehaviour.h"
#include "MoveComponent.h"
#include "Transform2D.h"
#include "Actor.h"
#include <random>
#include <time.h>

WanderBehaviour::WanderBehaviour(MoveComponent* moveComponenet, float force, float radius, float distance)
{
	srand(time(0));

	m_moveComponent = moveComponenet;
	m_force = force;
	m_radius = radius;
	m_circleDistance = distance;
}

void WanderBehaviour::update(float deltaTime)
{
	MathLibrary::Vector2 target = MathLibrary::Vector2((rand() % 200) - 100, (rand() % 200) - 100 );

	// Sets the target to be a point on the circle that surrounds the agent.
	MathLibrary::Vector2 targetCircle = getOwner()->getTransform()->getWorldPosition() + 
		(getOwner()->getTransform()->getForward() * m_circleDistance);

	target = (target.getNormalized() * m_radius) + targetCircle;
	
	m_desiredVelocity = (target -
		getOwner()->getTransform()->getWorldPosition()) * 
		m_force;

	m_steeringForce = m_desiredVelocity - m_currentVelocity;

	m_currentVelocity = m_currentVelocity + (m_steeringForce * deltaTime);

	MathLibrary::Vector2 newPosition = getOwner()->getTransform()->getWorldPosition();

	newPosition = newPosition + (m_currentVelocity * deltaTime);

	m_moveComponent->setVelocity(newPosition);
}
