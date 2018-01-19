#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt *(direction ? 1.0f : -1.0f) * speed, 0);
	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction =! direction;
		for(int i = 0; i < ships.size(); ++i){
			ships[i]->move(0, 24);
		}
	}
}
//setting static variables Invader
bool Invader::direction = true;
float Invader::speed = 20.0f;

//setting static variable Player
float Player::speed = 100.0f;
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Left) && this->getPosition().x > 0){
		move(dt * (-speed), 0);
	}
	if(Keyboard::isKeyPressed(Keyboard::Right) && this->getPosition().x < gameWidth) {
		move(dt * speed, 0);
	}
	static vector<Bullet*> bullets;
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		bullets.push_back(new Bullet(getPosition, false));
	}
}
