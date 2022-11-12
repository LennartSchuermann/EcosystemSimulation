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

	sf::Color color;
public:
	dna dna;

	Entity();
	Entity(Entity mother, Entity father);

	void InitEntity();

	void HandleScreenCollision();

	void Update();

	void HandleEntityCollision(std::vector<Entity>* entities, int* childrenAmount);

	int canCreateChild(const Entity* entity) const;

	sf::CircleShape getShape() const;

	sf::CircleShape getCollisionShape() const;
};