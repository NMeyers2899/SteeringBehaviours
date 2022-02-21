#include "Agent.h"
#include "FleeBehaviour.h"
#include "SeekBehaviour.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Agent::Agent()
{
	Actor::start();

	m_target = nullptr;
	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_spriteComponent = dynamic_cast<SpriteComponent*>(addComponent(new SpriteComponent("SpriteComponent", "Images/player.png")));
	m_fleeBehaviour = dynamic_cast<FleeBehaviour*>(addComponent(new FleeBehaviour(this, nullptr, m_moveComponent)));
}

Agent::Agent(float xPos, float yPos, Actor* target)
{
	Actor::start();

	m_target = target;
	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_spriteComponent = dynamic_cast<SpriteComponent*>(addComponent(new SpriteComponent("SpriteComponent", "Images/player.png")));
	m_fleeBehaviour = dynamic_cast<FleeBehaviour*>(addComponent(new FleeBehaviour(this, nullptr, m_moveComponent)));
}

void Agent::setTarget(Actor* value)
{
	m_target = value;
	m_fleeBehaviour->setTarget(value);
}
