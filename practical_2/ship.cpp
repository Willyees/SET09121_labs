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
void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}
bool Ship::is_exploded() const{ return _exploded; }
Ship::~Ship() = default;

//Invader
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
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; ++i) {
			ships[i]->move(0, 24);
		}
	}
	//puts cooldown on firetime and fires when <= 0
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}
	//wait for set time before remove invader
	static float destructionTime = 2.0f;
	for (auto &s : ships) {
		if (s->is_exploded()) {
			destructionTime -= dt;
		}
		if (destructionTime <= 0.0f) {
			s->setPosition(-100, -100);
			destructionTime = 2.0f;
		}
	}
}

void Invader::Explode() {
	Ship::Explode();
	speed += 1.0f;
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
	if (Keyboard::isKeyPressed(Keyboard::Left) && getPosition().x > 0){
		move(dt * (-speed), 0);
	}
	if(Keyboard::isKeyPressed(Keyboard::Right) && getPosition().x +32 < gameWidth) {
		move(dt * speed, 0);
	}
	//cool down on shooting
	static float firetime = 0.0f;
	firetime -= dt;
	if(firetime < 0 && Keyboard::isKeyPressed(Keyboard::Up)) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
	
}


void Player::Explode() {
	
}
