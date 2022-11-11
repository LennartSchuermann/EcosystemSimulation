#pragma once
#include "Entity.h"

Entity::Entity() {
	//gen, read dna & set data
	dna = CreateDNA();

	speed = dna.speed;
	size = dna.size;
	collisionRadius = dna.collisionRadius;
	lifeCounter = dna.maxAge;

	color = { (sf::Uint8)dna.color.r, (sf::Uint8)dna.color.g, (sf::Uint8)dna.color.b };

	InitEntity();
}

Entity::Entity(const Entity *mother, const Entity* father) {
	//generate child of two entities

	InitEntity();
}

void Entity::InitEntity() {
	shape.setRadius(size);
	shape.setFillColor(color);

	color.a = 100;	//alpha of collisionRadius
	collisionCircle.setRadius(size * collisionRadius);
	collisionCircle.setFillColor(color);

	position = { genRandomNumber(1, SCREENSIZE[0] - size),genRandomNumber(1, SCREENSIZE[1] - size) };
	velocity = { 1.0f, 1.0f };
}

void Entity::HandleScreenCollision() {
	if (shape.getPosition().x >= SCREENSIZE[0] - size || shape.getPosition().x <= 0.0f)
		velocity.x *= -1.0f;

	if (shape.getPosition().y >= SCREENSIZE[1] - size || shape.getPosition().y <= 0.0f)
		velocity.y *= -1.0f;
}

void Entity::Update() {
	position.x += (velocity.x * speed);
	position.y += (velocity.y * speed);

	shape.setPosition(position);
	collisionCircle.setPosition(position - sf::Vector2f(size * (collisionRadius - 1), size * (collisionRadius - 1)));

	HandleScreenCollision();

	lifeCounter--;
}

void Entity::HandleEntityCollision(std::vector<Entity> entities) {
	//if collision shapes overlap, do smth
}

sf::CircleShape Entity::getShape() {
	return this->shape;
}

sf::CircleShape Entity::getCollisionShape() {
	return this->collisionCircle;
}
