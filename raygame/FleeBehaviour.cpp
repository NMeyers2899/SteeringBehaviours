#include "FleeBehaviour.h"
#include "MoveComponent.h"
#include "Actor.h"

FleeBehaviour::FleeBehaviour()
{
	m_moveComponent = new MoveComponent();
	m_moveComponent->setMaxSpeed(50);

	m_owner = nullptr;
	m_target = nullptr;
}

FleeBehaviour::FleeBehaviour(Actor* owner, Actor* target, MoveComponent* moveComponent)
{
	m_owner = owner;
	m_target = target;
	m_moveComponent = moveComponent;
}

void FleeBehaviour::update(float deltaTime)
{
	// Sets the desired velocity to be away from the target.
	m_desiredVelocity =((m_owner->getTransform()->getWorldPosition() - 
		m_target->getTransform()->getWorldPosition()).normalize() * m_moveComponent->getMaxSpeed());
	
	// Sets the steering force to slowly adjust the current velocity to the desired velocity.
	m_steeringForce = m_desiredVelocity - m_moveComponent->getVelocity();

	m_moveComponent->setVelocity(m_steeringForce);
}
