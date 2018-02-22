#pragma once
#include "ecm.h"


class PickupComponent : public Component {
private:
	std::vector<std::shared_ptr<Entity>> _entities;
public:

	void addEntities(std::vector<std::shared_ptr<Entity>>& entities);
	void update(double dt) override;
	void render() override;

	PickupComponent() = delete;
	explicit PickupComponent(Entity* p);
	
	
};