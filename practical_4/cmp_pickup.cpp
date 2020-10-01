#include "cmp_pickup.h"
#include "cmp_actor_movement.h"
void PickupComponent::addEntities(std::vector<std::shared_ptr<Entity>>& entities)
{
	_entities = entities;
}
void PickupComponent::update(double dt)
{
	for (auto entity : _entities) {
		if (length(entity->getPosition() - _parent->getPosition()) < 30.0f) {
			ActorMovementComponent* cmp = entity->GetCompatibleComponent<ActorMovementComponent>();
			if (cmp != nullptr) {
				_parent->setForDelete();
				cmp->setSpeed(cmp->getSpeed() + 10.0f);//increase speed of moving entity
				std::cout << cmp->getSpeed() << std::endl;
				break;
			}
		}
	}
}

void PickupComponent::render() {//no render 
}

PickupComponent::PickupComponent(Entity* p) : Component(p) {}


