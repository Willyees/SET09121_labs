#include "bullet.h"
#include "game.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Bullet::Bullet(const sf::Vector2f &pos, const bool mode){
	setPosition(pos);
	_mode = mode;
	setTexture(spritesheet);
	if(_mode)
		setTextureRect(IntRect(32,32,32,32));
	else
		setTextureRect(IntRect(72,32,32,32))
	
}
void Bullet::Update(const float &dt) {
	move(0, dt * 200.0f *(_move ? 1.0f : -1.0f));
}