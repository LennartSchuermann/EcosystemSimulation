#pragma once
#include <SFML/Graphics.hpp>
#include "MathLib.h"
#include "Constants.h"
#include "ColorManager.h"
#include "DNASystem.cpp"

class Entity {
private:
	sf::CircleShape shape;
	sf::CircleShape collisionCircle;

	sf::Vector2f velocity;
	sf::Vector2f position;

	dna dna;
	float speed;
	float size;
	int collisionRadius;
public:
	float lifeCounter;

	Entity() {
		//gen, read dna & set data
		this->dna.CreateDNA();

		speed = dna.speed;
		size = dna.size;
		collisionRadius = dna.collisionRadius;
		lifeCounter = dna.maxAge;

		sf::Color color(dna.color.r, dna.color.g, dna.color.b);

		shape.setRadius(size);
		shape.setFillColor(color);

		color.a = 100;
		collisionCircle.setRadius(size * collisionRadius);
		collisionCircle.setFillColor(color);

		speed = genRandomNumber(1, 5);

		position = { genRandomNumber(1, SCREENSIZE[0] - size),genRandomNumber(1, SCREENSIZE[1] - size) };
		velocity = { 1.0f, 1.0f};
	}

	Entity(Entity mother, Entity father) {
		//generate child of two entities
	}

	void HandleScreenCollision() {
		if (shape.getPosition().x >= SCREENSIZE[0] - size || shape.getPosition().x <= 0.0f)
			velocity.x *= -1.0f;

		if (shape.getPosition().y >= SCREENSIZE[1] - size || shape.getPosition().y <= 0.0f)
			velocity.y *= -1.0f;
	}

	void Update() {
		position.x += (velocity.x * speed);
		position.y += (velocity.y * speed);

		shape.setPosition(position);
		collisionCircle.setPosition(position - sf::Vector2f(size * (collisionRadius - 1), size * (collisionRadius - 1)));

		HandleScreenCollision();

		lifeCounter--;
	}

	void HandleEntityCollision(std::vector<Entity> entities) {
		//if collision shapes overlap, do smth
	}

	sf::CircleShape getShape() {
		return this->shape;
	}

	sf::CircleShape getCollisionShape() {
		return this->collisionCircle;
	}
};