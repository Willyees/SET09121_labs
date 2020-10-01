#pragma once
#include "cmp_actor_movement.h"

class PlayerMovementComponent : public ActorMovementComponent{
	
	void render() override;
	void update(double dt) override;
public:
	PlayerMovementComponent(Entity* p);

};