#include "SeekBehaviour.h"
#include "MoveComponent.h"
#include "Actor.h"
#include <Vector2.h>

SeekBehaviour::SeekBehaviour()
{
	m_moveComponent = new MoveComponent();

	m_target = nullptr;
}

SeekBehaviour::SeekBehaviour(Actor* target, MoveComponent* moveComponent, float force)
{
	m_target = target;
	m_moveComponent = moveComponent;
	m_force = force;

	m_currentVelocity = m_moveComponent->getVelocity();
}

void SeekBehaviour::update(float deltaTime)
{
	if (getOwner() && m_target)
	{
		m_desiredVelocity = (m_target->getTransform()->getWorldPosition() - getOwner()->getTransform()->getWorldPosition()).getNormalized() * m_force;

		m_steeringForce = m_desiredVelocity - m_currentVelocity;

		m_currentVelocity = m_currentVelocity + (m_steeringForce * deltaTime);

		MathLibrary::Vector2 newPosition = getOwner()->getTransform()->getWorldPosition();

		newPosition = newPosition + (m_currentVelocity * deltaTime);

		getOwner()->getTransform()->setWorldPosition(newPosition);
	}
}
