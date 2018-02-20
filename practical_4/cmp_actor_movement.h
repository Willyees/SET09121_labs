#pragma once
#include "ecm.h"

class ActorMovementComponent : public Component {
protected:
	float _speed;
	bool validMove(const sf::Vector2f&);
	
public:
	explicit ActorMovementComponent(Entity* p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float speed);
	void move(const sf::Vector2f&);
	void move(float x, float y);

	void render() override;
	void update(double dt) override;
};