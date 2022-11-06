#include <SFML/Graphics.hpp>
#include "MathLib.h"
#include "Constants.h"
#include "ColorManager.h"

class Entity {
private:
	sf::CircleShape shape;
	sf::CircleShape collisionCircle;

	sf::Vector2f velocity;
	sf::Vector2f position;

	float speed;

	const float SIZE = 10.0f;
	const int COLLISIONRADIUS = 4;
public:
	Entity() {
		//rgb mix = mix2Colors({ 237, 235, 78 }, { 235, 64, 52 });
		rgb rC = createRandomRgb();
		sf::Color color(rC.r, rC.g, rC.b, 255);

		shape.setRadius(SIZE);
		shape.setFillColor(color);

		color.a = 100;
		collisionCircle.setRadius(SIZE * COLLISIONRADIUS);
		collisionCircle.setFillColor(color);

		speed = genRandomNumber(1, 5);

		position = { genRandomNumber(1, SCREENSIZE[0] - SIZE),genRandomNumber(1, SCREENSIZE[1] - SIZE) };
		velocity = { 1.0f, 1.0f};
	}

	void HandleScreenCollision() {
		if (shape.getPosition().x >= SCREENSIZE[0] - SIZE || shape.getPosition().x <= 0.0f)
			velocity.x *= -1.0f;

		if (shape.getPosition().y >= SCREENSIZE[1] - SIZE || shape.getPosition().y <= 0.0f)
			velocity.y *= -1.0f;
	}

	void Update() {
		position.x += (velocity.x * speed);
		position.y += (velocity.y * speed);

		shape.setPosition(position);
		collisionCircle.setPosition(position - sf::Vector2f(SIZE * (COLLISIONRADIUS - 1), SIZE * (COLLISIONRADIUS - 1)));

		HandleScreenCollision();
	}

	sf::CircleShape getShape() {
		return this->shape;
	}

	sf::CircleShape getCollisionShape() {
		return this->collisionCircle;
	}
};