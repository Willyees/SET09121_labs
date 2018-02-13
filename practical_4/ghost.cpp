#include "ghost.h"
#include <iostream>

using namespace std;
using namespace sf;

void Ghost::update(const double dt) {
	//srand(time(NULL));
	static Clock clock;
	double time =+ clock.getElapsedTime().asSeconds();
	cout << (time) << endl;
	if (time > 0.5) {
		randNumx = rand() % 3 - 1;
		randNumy = rand() % 3 - 1;
		clock.restart();
		time = 0;
	}
	Vector2f nextPos = Vector2f(randNumx * _speed * dt, randNumy *_speed * dt);
	cout << nextPos.x << " " << nextPos.y << endl;
	if (validMove(nextPos +_position)) {
		move(nextPos);
		cout << "ok" << endl;
		Entity::update(dt);
	}
	else {
		cout << "out" << endl;
		update(dt);
	}
	
}

void Ghost::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}

Ghost::Ghost(Vector2f* pos) :_speed(200.f), Entity(make_unique<CircleShape>(20.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
	_position = *pos;
}