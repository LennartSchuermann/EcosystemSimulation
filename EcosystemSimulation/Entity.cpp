#pragma once
#include "Entity.h"

Entity::Entity() {
	//gen, read dna & set data
	this->dna = CreateDNA();

	this->color = { (sf::Uint8)dna.color.r, (sf::Uint8)dna.color.g, (sf::Uint8)dna.color.b };
	this->position = { genRandomNumber(dna.size, SCREENSIZE[0] - dna.size),genRandomNumber(dna.size, SCREENSIZE[1] - dna.size) };
	this->velocity = { 1.0f, 1.0f };

	InitEntity();
}

Entity::Entity(const Entity& mother, const Entity& father) {
	//generate child of two entities
	this->dna = GenerateDNA(&mother.dna, &father.dna);

	this->color = { (sf::Uint8)dna.color.r, (sf::Uint8)dna.color.g, (sf::Uint8)dna.color.b };
	this->position = { mother.getShape().getPosition().x,mother.getShape().getPosition().y };
	this->velocity = { mother.velocity.x, -mother.velocity.y };

	InitEntity();
}

void Entity::InitEntity() {
	shape.setRadius(dna.size);
	shape.setFillColor(color);

	this->color.a = 100;	//alpha of collisionRadius
	collisionCircle.setRadius(dna.size * (float)dna.collisionRadius);
	collisionCircle.setFillColor(color);

	shape.setPosition(position);
	collisionCircle.setPosition(position - sf::Vector2f(dna.size * ((float)dna.collisionRadius - 1), 
		dna.size * ((float)dna.collisionRadius - 1)));
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

	dna.currentLifeTime++;
}

void Entity::HandleEntityCollision(std::vector<Entity> &entities, int& childrenAmount) {
	//if collision shapes overlap, do smth
	
	for (auto& entity : entities) {
		if (this != &entity) {
			float dx = (collisionCircle.getPosition().x + ((float)dna.collisionRadius * dna.size / 2)) - (entity.getCollisionShape().getPosition().x
				+ ((float)entity.dna.collisionRadius * entity.dna.size / 2));
			float dy = (collisionCircle.getPosition().y + ((float)dna.collisionRadius * dna.size / 2)) - (entity.getCollisionShape().getPosition().y
				+ ((float)entity.dna.collisionRadius * entity.dna.size / 2));

			float distance = std::sqrt((dx * dx) + (dy * dy));

			if (distance <= ((float)dna.collisionRadius * dna.size) + ((float)entity.dna.collisionRadius * entity.dna.size)) {
				if (this->canCreateChild(entity)) {
					//create children
					auto child = Entity(*this, entity);
					entities.push_back(child);

					childrenAmount++;

					dna.reproductionRate += dna.reproductionRate;
					entity.dna.currentLifeTime += entity.dna.reproductionRate;
				}
			}
		}
	}
}

int Entity::canCreateChild(const Entity& entity) const {
	if (dna.currentLifeTime >= dna.reproductionRate && entity.dna.currentLifeTime >= entity.dna.reproductionRate 
		&& dna.gender != entity.dna.gender) {
		return true;
	}

	return false;
}

sf::CircleShape Entity::getShape() const {
	return this->shape;
}

sf::CircleShape Entity::getCollisionShape() const {
	return this->collisionCircle;
}
