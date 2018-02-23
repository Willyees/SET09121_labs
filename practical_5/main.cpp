#include "Box2D\Box2D.h"
#include "SFML/Graphics.hpp"

b2World* world;

using namespace sf;
using namespace std;

const float physics_scale = 30.0f;
const float physics_scale_inv = 1 / physics_scale;
const int gameHeight = 800;
const int gameWidth = 600;

vector<b2Body*> bodies;
vector<RectangleShape*> sprites;

//convert from b2Vec2 to a Vector2f
inline const sf::Vector2f bv2_to_sv2(const b2Vec2& in) {
	return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}

//convert from vector2f to b2vec2 
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
	return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}

//convert from screenspace.y to physics.y (physics has y positive towards top of screen - opposite)
inline const Vector2f invert_height(const Vector2f& in) {
	return Vector2f(in.x, gameHeight - in.y);
}

//create a box3d body with a box fixture
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic,
	const Vector2f& position, const Vector2f& size) {

	b2BodyDef BodyDef;
	//dynamic (moving) or static (not moving) ?
	BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(position);
	//create the body
	b2Body* body = World.CreateBody(&BodyDef);

	//create the fixture shape
	b2PolygonShape Shape;
	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	b2FixtureDef FixtureDef;
	//fixture properties
	FixtureDef.density = dynamic ? 10.0f : 0.f;
	FixtureDef.friction = dynamic ? 0.8f : 1.1f;
	FixtureDef.restitution = 1.0f;
	FixtureDef.shape = &Shape;
	//add to body
	body->CreateFixture(&FixtureDef);
	return body;
}

//create a box2d body with a box fixture. from sfml::rectangle
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic,
					     const RectangleShape& rs) {
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void init() {
	const b2Vec2 gravity(0.0f, -10.0f);

	//constuct a world, which holds and simulates the physics bodies
	world = new b2World(gravity);

	//create boxes
	for (int i = 1; i < 11; i++) {
		//create sfml shapes for each box
		auto s = new RectangleShape();
		s->setPosition(Vector2f(i * (gameWidth / 12.f), gameHeight * 0.7f));
		s->setSize(Vector2f(50.f, 50.f));
		s->setOrigin(Vector2f(25.f, 25.f));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		//create a dynamic physics body fot the box
		auto b = CreatePhysicsBox(*world, true, *s);
		//give the box a spin
		b->ApplyAngularImpulse(5.0f, true);
		bodies.push_back(b);
	}
}

int main(){
	init();

	return 0;
}