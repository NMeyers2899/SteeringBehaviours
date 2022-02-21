#include "FleeBehaviour.h"
#include "MoveComponent.h"
#include "Actor.h"

FleeBehaviour::FleeBehaviour()
{
	m_moveComponent = new MoveComponent();
	m_moveComponent->setMaxSpeed(50);
	m_force = 0;
	m_target = nullptr;
}

FleeBehaviour::FleeBehaviour(Actor* target, MoveComponent* moveComponent, float force)
{
	m_target = target;
	m_moveComponent = moveComponent;
	m_force = force;

	m_currentVelocity = m_moveComponent->getVelocity();
}

void FleeBehaviour::update(float deltaTime)
{
	if (getOwner() && m_target)
	{
		m_desiredVelocity = (getOwner()->getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).getNormalized() * m_force;

		m_steeringForce = m_desiredVelocity - m_currentVelocity;

		m_currentVelocity = m_currentVelocity + (m_steeringForce * deltaTime);

		MathLibrary::Vector2 newPosition = getOwner()->getTransform()->getWorldPosition();

		newPosition = newPosition + (m_currentVelocity * deltaTime);

		getOwner()->getTransform()->setWorldPosition(newPosition);
	}
}
