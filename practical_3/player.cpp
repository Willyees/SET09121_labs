#include "player.h"
using namespace sf;
using namespace std;

void Player::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		move(Vector2f(0,-_speed * dt));
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f( -_speed * dt, 0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		move(Vector2f(0, _speed * dt));
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f( _speed * dt, 0));
	}
	Entity::update(dt);
}

Player::Player()
		: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
	
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}