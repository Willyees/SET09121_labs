#pragma once
#include <SFML/Graphics.hpp>
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum state {DEADEND, ROAMING, ROTATING, ROTATED};
	state _state;

	void update(double dt) override;
	void render() override;
public:
	EnemyAIComponent(Entity* p);
};