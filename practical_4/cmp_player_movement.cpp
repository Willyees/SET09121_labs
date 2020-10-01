#include "cmp_player_movement.h"
#include "SFML\Graphics.hpp"

using namespace sf;
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-dt * _speed, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		move(Vector2f(0, -dt * _speed));
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(dt * _speed, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		move(Vector2f(0, dt * _speed));
	}
}

void PlayerMovementComponent::render() {
	
}
