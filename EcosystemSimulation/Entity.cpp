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

	float speed;
	float size;
	int collisionRadius;
	sf::Color color;
public:
	dna dna;
	float lifeCounter;

	Entity() {
		//gen, read dna & set data
		dna = CreateDNA();

		speed = dna.speed;
		size = dna.size;
		collisionRadius = dna.collisionRadius;
		lifeCounter = dna.maxAge;

		color = { (sf::Uint8)dna.color.r, (sf::Uint8)dna.color.g, (sf::Uint8)dna.color.b };

		InitEntity();
	}

	Entity(Entity mother, Entity father) {
		//generate child of two entities

		InitEntity();
	}

	void InitEntity() {
		shape.setRadius(size);
		shape.setFillColor(color);

		color.a = 100;	//alpha of collisionRadius
		collisionCircle.setRadius(size * collisionRadius);
		collisionCircle.setFillColor(color);

		position = { genRandomNumber(1, SCREENSIZE[0] - size),genRandomNumber(1, SCREENSIZE[1] - size) };
		velocity = { 1.0f, 1.0f };
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