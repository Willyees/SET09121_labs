#include "ship.h"
#include "game.h"
#include <iostream>
using namespace sf;
using namespace std;

vector<Ship*>ships;
Invader invader;
Sprite sprite;
Texture spritesheet;

void Update(RenderWindow &window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();
	for (auto &s : ships) {
		s->Update(dt);
	}

	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	//Quit via esc key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window) {
	for (const auto s : ships) {
		window.draw(*s);
	}
}

void Load() {
	//creating list of invaders
	for(int i = 0; i < invaders_rows; i++){
		for (int j = 0; j < invaders_columns; j++) {
			Invader* inv = new Invader(sf::IntRect(32 * i, 0,32 , 32), { 100.0f + j*50.0f,100.0f + i*50.0f});
			ships.push_back(inv);
		}
	}
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << endl;
	}
	
	
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}