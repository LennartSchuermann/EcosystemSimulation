#pragma once
#include <SFML/Graphics.hpp>
#include "MathLib.h"
#include "DNASystem.cpp"

class Entity
{
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

	Entity();
	Entity(Entity mother, Entity father);

	void InitEntity();

	void HandleScreenCollision();

	void Update();

	void HandleEntityCollision(std::vector<Entity> entities);

	sf::CircleShape getShape();

	sf::CircleShape getCollisionShape();
};
