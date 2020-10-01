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
Font font;
Text text;
int scoreLx = 0;
int scoreRx = 0;

void Reset() {
	//Reset paddle position 
	paddles[0].setPosition(10 + paddleSize.x /2.f, gameHeight / 2);
	paddles[1].setPosition(-10 + gameWidth - paddleSize.x / 2.f , gameHeight / 2);
	//reset ball position
	ball.setPosition(gameWidth /2, gameHeight /2);
	ballVelocity = {(server ? 100.0f : -100.0f), 60.0f};
	text.setString(std::to_string(scoreLx) + "\t:\t"+ std::to_string(scoreRx));
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Load(){
	//Load font-face from res dir
	font.loadFromFile("res/fonts/ANUDI.ttf");
	//set text element to use font
	text.setFont(font);
	//char size to 24 px
	text.setCharacterSize(24);
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
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0,-10);
	} else if(by < 0) {
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0,10);
	} else if(bx > gameWidth) {
		//right wall
		scoreLx ++;
		Reset();
	} else if(bx < 0) {
		//left wall
		scoreRx ++;
		Reset();
	} else if (
	  //ball is inline or behind paddle
	  bx < paddleSize.x +10 && 
	  //AND ball is below top edge of paddle
	  by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && 
	  //AND ball is above bottom edge of paddle
	  by < paddles[0].getPosition().y +(paddleSize.y * 0.5)
	  ) {
		//bounce off left paddle	
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
	} else if (
	  //ball is inline or behind paddle
	  bx > gameWidth - paddleSize.x -10 &&
	  //AND ball is below top edge of paddle
	  by > paddles[1].getPosition().y -(paddleSize.y * 0.5) &&
	  //AND ball is above bottom edge of paddle
	  by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {
		//bounce off the right paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;

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
	
	//handle paddle movement Player
	float directionLx = 0.0f;
	float directionRx = 0.0f;
	if(Keyboard::isKeyPressed(controls[0]) && (paddles[0].getPosition().y - paddleSize.y / 2) > 0) {
		directionLx --;
	}
	if(Keyboard::isKeyPressed(controls[1]) && (paddles[0].getPosition().y + paddleSize.y / 2) < gameHeight) {
		directionLx ++;
	}
	if (Keyboard::isKeyPressed(controls[2]) && (paddles[1].getPosition().y - paddleSize.y / 2) > 0) {
		directionRx --;
	}
	if (Keyboard::isKeyPressed(controls[3]) && (paddles[1].getPosition().y + paddleSize.y / 2) < gameHeight) {
		directionRx ++;
	}
	
	//handle paddle movement AI
	//check if ball is over or under than paddle, then direction of paddle will be set accordingly
	if (ball.getPosition().y < paddles[0].getPosition().y && (paddles[0].getPosition().y - paddleSize.y / 2) > 0) {
		directionLx --;
	} 
	else if (ball.getPosition().y > paddles[0].getPosition().y && (paddles[0].getPosition().y + paddleSize.y / 2) < gameHeight) {
		directionLx ++;
	}
	if (ball.getPosition().y < paddles[1].getPosition().y && (paddles[1].getPosition().y - paddleSize.y / 2) > 0) {
		directionRx --;
	}
	else if (ball.getPosition().y > paddles[0].getPosition().y && (paddles[1].getPosition().y + paddleSize.y / 2) < gameHeight) {
		directionRx ++;
	}

	paddles[0].move(0, directionLx * paddleSpeed * dt);
	paddles[1].move(0, directionRx * paddleSpeed * dt);
}

void Render(RenderWindow &window) {
	//draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
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