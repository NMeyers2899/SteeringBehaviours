#include "Agent.h"
#include "FleeBehaviour.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Agent::Agent() : Actor(0, 0, "agent")
{
	m_target = nullptr;
}

Agent::Agent(float xPos, float yPos, Actor* target, float fleeForce, float seekForce,
	float wanderForce) : Actor(xPos, yPos, "agent")
{
	m_target = target;
	m_fleeForce = fleeForce;
	m_seekForce = seekForce;
	m_wanderForce = wanderForce;
}

void Agent::start()
{
	Actor::start();

	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_moveComponent->setMaxSpeed(250);
	m_spriteComponent = dynamic_cast<SpriteComponent*>(addComponent(new SpriteComponent("SpriteComponent", "Images/enemy.png")));
	m_fleeBehaviour = dynamic_cast<FleeBehaviour*>(addComponent(new FleeBehaviour(m_target, m_moveComponent, m_fleeForce)));
	m_seekBehaviour = dynamic_cast<SeekBehaviour*>(addComponent(new SeekBehaviour(m_target, m_moveComponent, m_seekForce)));
	m_wanderBehaviour = dynamic_cast<WanderBehaviour*>(addComponent(new WanderBehaviour(m_moveComponent, m_wanderForce, 10, 50)));
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

	if (m_moveComponent->getVelocity().getMagnitude() > m_maxSpeed)
		m_moveComponent->setVelocity(m_moveComponent->getVelocity().getNormalized() * m_maxSpeed);
}

void Agent::setTarget(Actor* value)
{
	m_target = value;
	m_fleeBehaviour->setTarget(value);
}
