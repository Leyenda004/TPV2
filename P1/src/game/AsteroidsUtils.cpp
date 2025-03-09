#include "AsteroidsUtils.h"

#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Game.h"

#include "../components/Transform.h"
#include "../components/Generations.h"
#include "../components/ImageWithFrames.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Follow.h"
#include "../components/TowardDestination.h"

AsteroidsUtils::AsteroidsUtils()
{

}

void AsteroidsUtils::create_asteroids(int n)
{
	if (n <= 0) return;

	float posX = sdlutils().rand().nextInt(0, sdlutils().width());
	float posY = sdlutils().rand().nextInt(0, sdlutils().height());
	Vector2D randomAsteroidPos = Vector2D(posX, posY);

	int borderPosConfig = sdlutils().rand().nextInt(0, 4);
	
	switch (borderPosConfig)
	{
		case 0: randomAsteroidPos.setX(10); break;
		case 1: randomAsteroidPos.setY(10); break;
		case 2: randomAsteroidPos.setX(sdlutils().width() - 10);  break;
		case 3: randomAsteroidPos.setY(sdlutils().height() - 10); break;
	}

	float targetX = sdlutils().rand().nextInt(-100, 100) + sdlutils().width() / 2;
	float targetY = sdlutils().rand().nextInt(-100, 100) + sdlutils().height() / 2;
	Vector2D randomTargetPos = Vector2D(targetX, targetY);

	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
	Vector2D v = (randomTargetPos - randomAsteroidPos).normalize() * speed;

	int generations = sdlutils().rand().nextInt(1, 4);

	ecs::entity_t newAsteroid = Game::Instance()->getMngr()->addEntity(ecs::grp::ASTEROIDS);
	
	newAsteroid->getMngr()->addComponent<Generations>(newAsteroid, generations);
	newAsteroid->getMngr()->addComponent<Transform>(newAsteroid, randomAsteroidPos, v, 10*generations, 10* generations, 0);
	newAsteroid->getMngr()->addComponent<ImageWithFrames>(newAsteroid, &sdlutils().images().at("asteroids"), 25, 5, 6);
	newAsteroid->getMngr()->addComponent<ShowAtOppositeSide>(newAsteroid);

	if (sdlutils().rand().nextInt(0, 2) == 0)
	{
		newAsteroid->getMngr()->addComponent<TowardDestination>(newAsteroid);
	}
	else
	{
		auto fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
		Transform* fighterTr = Game::Instance()->getMngr()->getComponent<Transform>(fighter);

		newAsteroid->getMngr()->addComponent<Follow>(newAsteroid, fighterTr);
	}

	create_asteroids(n - 1);
}

void AsteroidsUtils::remove_all_asteroids()
{
	auto asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);

	for (ecs::entity_t asteroid : asteroids)
	{
		asteroid->getMngr()->setAlive(asteroid, false);
	}
}

void AsteroidsUtils::split_astroid(ecs::Entity* a)
{
	a->getMngr()->setAlive(a, false);

	int generations = a->getMngr()->getComponent<Generations>(a)->getGenerations();

	if (generations <= 0) return; // Only if has gerenation value > 0

	Transform* tr = a->getMngr()->getComponent<Transform>(a);

	for (int i = 0; i < generations; ++i)
	{
		int r = sdlutils().rand().nextInt(0, 360);
		Vector2D pos = tr->getPos() + tr->getVel().rotate(r) * 2 * std::max(tr->getWidth(), tr->getHeight());
		Vector2D vel = tr->getVel().rotate(r) * 1.1f;
		int newGens = generations - 1;

		auto newAsteroid = a->getMngr()->addEntity(ecs::grp::ASTEROIDS);
		newAsteroid->getMngr()->addComponent<Generations>(newAsteroid, newGens);
		newAsteroid->getMngr()->addComponent<Transform>(newAsteroid, pos, vel, 10 * newGens, 10 * newGens, 0);
		newAsteroid->getMngr()->addComponent<ImageWithFrames>(newAsteroid, &sdlutils().images().at("asteroids"), 30, 5, 6);
		newAsteroid->getMngr()->addComponent<ShowAtOppositeSide>(newAsteroid);
	}
	
}
