#include "cmp_actor_movement.h"
#include "LevelSystem.h"

using namespace sf;

void ActorMovementComponent::update(double dt) {}
void ActorMovementComponent::render() {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.f), Component(p) {
	//set an entity as a parent

}

bool ActorMovementComponent::validMove(const Vector2f& pos) {
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}


void ActorMovementComponent::move(const Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}


float ActorMovementComponent::getSpeed() const{
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}