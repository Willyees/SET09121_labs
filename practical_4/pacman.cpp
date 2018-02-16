#define GHOSTS_COUNT 4

#include "pacman.h"
#include "ghost.h"
#include "player.h"
#include "system_renderer.h"
#include "cmp_sprite.h"
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

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	_ents.render(Renderer::getWindow());
	//render clock and text adding to the queue RENDERER::
}

void GameScene::load() {
	//Was creating player and ghost in this way before introduction of components
	/* 
	shared_ptr<Player> player = make_shared<Player>();
	_ents.list.push_back(player);
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Ghost> ghost = make_shared<Ghost>(new Vector2f(100, 100));
		_ents.list.push_back(ghost);
	}*/
	{
		auto pl = make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(pl);
	}

	const sf::Color ghost_col[]{ { 208, 62, 25 },//red
	{ 45, 133,28 } ,//orange
	{ 70, 191, 238 },//cyan
	{ 234, 130, 229 } };//pink


	for (int i = 0; i < GHOSTS_COUNT; i++) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_col[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);
	}
}


