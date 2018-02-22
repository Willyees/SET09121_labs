#include "entityManager.h"

void EntityManager::update(double dt) {
	
	for (auto item : list) {
		item->update(dt);
	}
}


void EntityManager::render(sf::RenderWindow &window) {
	
	for (int i = 0; i < list.size(); i++) {

		if (list[i]->is_fordeletion())
		{
			list.erase(list.begin() + i);
		}
		list[i]->render();
	}
}