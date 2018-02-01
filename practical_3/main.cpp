#include "entity.h"
#include "player.h"

using namespace std;
using namespace sf;

Player* player;
void Load() {
	player = new Player();
	//player->setPosition()
}
void Update(RenderWindow &window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();
	player->update(dt);
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
	player->render(window);
}


int main() {
	RenderWindow window(VideoMode(800,600), "labyrinth");
	Load();
	while(window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}