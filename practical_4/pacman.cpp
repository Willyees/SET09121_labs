#define GHOSTS_COUNT 4

#include "pacman.h"
#include "ghost.h"
#include "player.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
#include "cmp_player_movement.h"
#include "cmp_ghost_movement.h"
#include "levelsystem.h"
#include "cmp_enemy_ai.h"
#include "cmp_pickup.h"
#include <iostream>
#include <memory>


using namespace std;
using namespace sf;
//using namespace System;
//using namespace System::IO;

std::shared_ptr<Scene> gameScene = std::make_shared<GameScene>();
std::shared_ptr<Scene> menuScene = std::make_shared<MenuScene>();
std::shared_ptr<Scene> activeScene;
Font font;
//MenuScene

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	
	
	
}

void MenuScene::render() {
	_ents.render(Renderer::getWindow());
	Renderer::queue(&text);
}

void MenuScene::load() {
	if (!font.loadFromFile("res/fonts/Royal Twins.ttf")) {
		cout << "font not existing!" << endl;
		//cout << Directory::GetCurrentDirectory() << endl;
	}
	text.setFont(font); 
	text.setCharacterSize(64);
	text.setString("Almost Pacman");
	text.setPosition((350.f) - text.getLocalBounds().width * 0.5f, 100);
	
}

MenuScene::MenuScene() {

}


//Game Scene
shared_ptr<Entity> pl;
vector<shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> nibbles;

shared_ptr<Entity> GameScene::makeNibble(const Vector2ul& nl, bool big) {
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	if(big) {
		s->setShape<sf::CircleShape>(10.f);
		s->getShape().setOrigin({ 10.f, 10.f });
		s->getShape().setFillColor(Color::Blue);

	}
	else {
		s->setShape<sf::CircleShape>(6.f);
		s->getShape().setOrigin({ 6.f, 6.f });
		s->getShape().setFillColor(Color::White);
	}
	cherry->addComponent<PickupComponent>();
	vector<shared_ptr<Entity>> entities_to_check(ghosts);
	entities_to_check.push_back(pl);
	cherry->GetCompatibleComponent<PickupComponent>()->addEntities(entities_to_check);
	cherry->setPosition(ls::getTilePosition(nl) + Vector2f(12.5f, 12.5f));
	
	return cherry;
}

void GameScene::respawn() {

	pl->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(12.5f, 12.5f));//setting player inside the track (half tiles)
	pl->GetCompatibleComponent<ActorMovementComponent>()->setSpeed(150.0f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]) + Vector2f(12.5f, 12.5f));
		g->GetCompatibleComponent<ActorMovementComponent>()->setSpeed(100.0f);
	}
	//clear remaining nibbles
	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	//white nibbles
	auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, false);
		_ents.list.push_back(cherry);
	}
	//blue nibbles
	nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, true);
		_ents.list.push_back(cherry);
	}
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	for (auto& g : ghosts) {
		if (length(g->getPosition() - pl->getPosition()) < 25.0f)
			respawn();
	}
	Scene::update(dt);
}

void GameScene::render() {
	ls::render(Renderer::getWindow());
	_ents.render(Renderer::getWindow());
	//render clock and text adding to the queue RENDERER::
}

void GameScene::load() {
	
	ls::loadLevelFile("res/pacman.txt", 25.0f);
	{
		pl = make_shared<Entity>();
		pl->addComponent<PlayerMovementComponent>();
		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		pl->setPosition(Vector2f(100.0f, 100.0f));

		_ents.list.push_back(pl);
	}

	const sf::Color ghost_col[]{ { 208, 62, 25 },//red
	{ 45, 133,28 } ,//orange
	{ 70, 191, 238 },//cyan
	{ 234, 130, 229 } };//pink


	for (int i = 0; i < GHOSTS_COUNT; i++) {
		auto ghost = make_shared<Entity>();
		ghost->addComponent<EnemyAIComponent>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_col[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		ghosts.push_back(ghost);
		_ents.list.push_back(ghost);
	}
	respawn();
}


