#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A, //Player1 UP
	Keyboard::Z, //Player1 Down
	Keyboard::Up, //Player2 Up
	Keyboard::Down //Player2 Down
};
const Vector2f paddleSize(26.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];
Vector2f ballVelocity;
bool server = false;

void Reset() {
	//Reset paddle position 
	paddles[0].setPosition(10 + paddleSize.x /2.f, gameHeight / 2);
	paddles[1].setPosition(-10 + gameWidth - paddleSize.x / 2.f , gameHeight / 2);
	//reset ball position
	ball.setPosition(gameWidth /2, gameHeight /2);
	ballVelocity = {(server ? 100.0f : -100.0f), 60.0f};
}

void Load(){
	//Set size and origin of paddles
	for(auto &p : paddles){
		p.setSize(paddleSize - Vector2f(3,3));
		p.setOrigin(paddleSize / 2.f);
	}
	//Set size and origin ball
	ball.setRadius(ballRadius -3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	Reset();
}

void Update(RenderWindow & window) {
	//reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	ball.move(ballVelocity * dt);
	//check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if(by > gameHeight) {
		//bottom wall
		ballVelocity.x = 1.1f;
		ballVelocity.y = -1.1f;
		ball.move(0,-10);
	} else if(by < 0) {
		//top wall
		ballVelocity.x = 1.1f;
		ballVelocity.y = -1.1f;
		ball.move(0,10);
	} else if(bx > gameWidth) {
		//right wall
		Reset();
	} else if(bx < 0) {
		//left wall
		Reset();
	}
	
	//check and consume events
	Event event;
	while(window.pollEvent(event)) {
		if(event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	
	//Quit via esc key
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		window.close();
	}
	
	//handle paddle movement
	float direction = 0.0f;
	if(Keyboard::isKeyPressed(controls[0])) {
		direction --;
	}
	if(Keyboard::isKeyPressed(controls[1])) {
		direction ++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);
}

void Render(RenderWindow &window) {
	//draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}
int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while(window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}