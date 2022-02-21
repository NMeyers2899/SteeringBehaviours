#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "MainScene.h"
#include "Player.h"
#include "Agent.h"

void MainScene::start()
{
	Player* player = new Player(50, 50, "Player");
	player->getTransform()->setScale({ 50, 50 });

	Agent* agent1 = new Agent(200, 200, player);
	agent1->getTransform()->setScale({ 50, 50 });

	addActor(player);
	addActor(agent1);
}
