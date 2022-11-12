#pragma once
#include "Entity.h"

Entity::Entity() {
	//gen, read dna & set data
	dna = CreateDNA();

	color = { (sf::Uint8)dna.color.r, (sf::Uint8)dna.color.g, (sf::Uint8)dna.color.b };

	InitEntity();
}

Entity::Entity(Entity mother, Entity father) {
	//generate child of two entities
	dna = GenerateDNA(&mother.dna, &father.dna);

	color = { (sf::Uint8)dna.color.r, (sf::Uint8)dna.color.g, (sf::Uint8)dna.color.b };

	InitEntity();
}

void Entity::InitEntity() {
	shape.setRadius(dna.size);
	shape.setFillColor(color);

	color.a = 100;	//alpha of collisionRadius
	collisionCircle.setRadius(dna.size * (float)dna.collisionRadius);
	collisionCircle.setFillColor(color);

	position = { genRandomNumber(1, SCREENSIZE[0] - dna.size),genRandomNumber(1, SCREENSIZE[1] - dna.size) };
	velocity = { 1.0f, 1.0f };
}

void Entity::HandleScreenCollision() {
	if (shape.getPosition().x >= SCREENSIZE[0] - dna.size || shape.getPosition().x <= 0.0f)
		velocity.x *= -1.0f;

	if (shape.getPosition().y >= SCREENSIZE[1] - dna.size || shape.getPosition().y <= 0.0f)
		velocity.y *= -1.0f;
}

void Entity::Update() {
	position.x += (velocity.x * dna.speed);
	position.y += (velocity.y * dna.speed);

	shape.setPosition(position);
	collisionCircle.setPosition(position - sf::Vector2f(dna.size * ((float)dna.collisionRadius - 1), dna.size * ((float)dna.collisionRadius - 1)));

	HandleScreenCollision();

	dna.maxAge--;
}

void Entity::HandleEntityCollision(std::vector<Entity> *entities) const {
	//if collision shapes overlap, do smth
	
	for (auto const& entity : *entities) {
		if (this != &entity) {
			float dx = (collisionCircle.getPosition().x + (dna.collisionRadius * dna.size / 2)) - (entity.getCollisionShape().getPosition().x
				+ (entity.dna.collisionRadius * entity.dna.size / 2));
			float dy = (collisionCircle.getPosition().y + (dna.collisionRadius * dna.size / 2)) - (entity.getCollisionShape().getPosition().y
				+ (entity.dna.collisionRadius * entity.dna.size / 2));

			float distance = std::sqrt((dx * dx) + (dy * dy));

			if (distance <= (dna.collisionRadius * dna.size) + (entity.dna.collisionRadius * entity.dna.size)) {
				//Do smth
				//std::cout << "Collision!" << std::endl;
			}
		}
	}
}

sf::CircleShape Entity::getShape() const {
	return this->shape;
}

sf::CircleShape Entity::getCollisionShape() const {
	return this->collisionCircle;
}
