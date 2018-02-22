#include "cmp_enemy_ai.h"
#include "levelsystem.h"
#include <iostream>

using namespace sf;


static const Vector2i directions[] = { {1,0},{0,1},{0,-1},{-1,0} };

void EnemyAIComponent::update(double dt){
	//amount to move
	const auto mva = (float)(dt * _speed);
	//current position
	const Vector2f pos = _parent->getPosition();
	//next position
	const Vector2f newpos = pos + _direction * mva;
	//inverse of our current direction
	const Vector2i baddir = -1 * Vector2i(_direction);
	//random new direction
	Vector2i newdir = directions[(rand() % 4)];

	switch (_state)
	{
	case EnemyAIComponent::ROAMING:
		if (ls::getTileAt(newpos) == ls::WALL || ls::getTileAt(newpos) == ls::WAYPOINT){ //wall in front or at waypoint
			//start rotate
			_state = ROTATING;
		}
		else
		{
			move(_direction * mva);
		}
		break;
	case EnemyAIComponent::DEADEND://not sure if it is needed
		
		break;
	case EnemyAIComponent::ROTATING:
		while (newdir == baddir || (ls::getTileAt(Vector2f(newdir) * mva + pos) == ls::WALL)) { 
			//direction is opposite and direction will lead to a wall
			newdir = directions[(rand() % 4)];
		}
		_direction = Vector2f(newdir);
		_state = ROTATED;
		break;
	case EnemyAIComponent::ROTATED:
		//have left the waypoint?
		if (ls::getTileAt(pos) != ls::WAYPOINT) {
			_state = ROAMING; //yes
		}
			move(_direction * mva); //no
		break;
	default:
		break;
	}
	ActorMovementComponent::update(dt);//empty (?)
}

void EnemyAIComponent::render() {}
EnemyAIComponent::EnemyAIComponent(Entity* p) :
	ActorMovementComponent(p), _state(ROAMING), _direction(directions[(rand() % 4)]){}