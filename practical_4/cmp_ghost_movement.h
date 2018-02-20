#pragma once
#include "cmp_actor_movement.h"

class GhostMovementComponent : public ActorMovementComponent {
	void render() override;
	void update(double dt) override;
public:
	GhostMovementComponent(Entity* p);
};