#pragma once
#include "Constants.h"
#include "ColorManager.h"
#include <SFML/Graphics.hpp>
#include "MathLib.h"
#include "DNASystem.h"

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
	int lifeCounter;

	Entity();
	Entity(const Entity* mother, const Entity* father);

	void InitEntity();

	void HandleScreenCollision();

	void Update();

	void HandleEntityCollision(std::vector<Entity> entities);

	sf::CircleShape getShape();

	sf::CircleShape getCollisionShape();
};