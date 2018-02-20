#include "cmp_ghost_movement.h"
#include "SFML\Graphics.hpp"

using namespace sf;
void GhostMovementComponent::update(double dt){
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		move(Vector2f(-dt * _speed, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		move(Vector2f(0, -dt * _speed));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		move(Vector2f(dt * _speed, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		move(Vector2f(0, dt * _speed));
	}
}

void GhostMovementComponent::render() {}
GhostMovementComponent::GhostMovementComponent(Entity* p) :
	ActorMovementComponent(p) {}