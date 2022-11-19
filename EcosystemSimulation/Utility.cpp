#include "Entity.h"

struct lessThan
{
	inline bool operator() (const Entity& a, const Entity& b) const
	{
		return (a.MinCS() < b.MinCS());
	}
};

inline std::vector<Entity> sortByX(std::vector<Entity> &entities) {
	std::sort(entities.begin(), entities.end(), lessThan());

	return entities;
}

inline bool isDNAEqual(const dna& a, const dna& b) {
	if (a.size == b.size && a.speed == b.speed && a.maxAge == b.maxAge && a.reproductionRate == b.reproductionRate
		&& a.collisionRadius == b.collisionRadius) {
		return true;
	}
	return false;
}


inline std::vector<std::vector<Entity*>> SweepAndPrune(std::vector<Entity> &axisList) {
	axisList = sortByX(axisList);

	std::vector<Entity*> activeList;
	std::vector<std::vector<Entity*>> pairs;

	for (auto i = 0; i < axisList.size(); ++i) {
		for (auto j = 0; j < activeList.size(); ++j) {
			if (axisList[i].MinCS() > activeList[j]->MaxCS()) {
				activeList.erase(activeList.begin() + j);
				j--;
			}
			else {
				if (!isDNAEqual(axisList[i].dna, activeList[j]->dna)) {
					std::vector<Entity*> mpair;
					mpair.push_back(&axisList[i]);
					mpair.push_back(activeList[j]);
					pairs.push_back(mpair);
				}
			}
		}
		activeList.push_back(&axisList[i]);
	}

	return pairs;
}


inline void CheckEntityCollision(Entity* a, Entity* b, int& childrenAmount, std::vector<Entity> &entities) {
	if (!isDNAEqual(a->dna, b->dna)) {
		float dx = (a->getCollisionShape().getPosition().x + ((float)a->dna.collisionRadius * a->dna.size / 2)) - (b->getCollisionShape().getPosition().x
			+ ((float)b->dna.collisionRadius * b->dna.size / 2));
		float dy = (a->getCollisionShape().getPosition().y + ((float)a->dna.collisionRadius * a->dna.size / 2)) - (b->getCollisionShape().getPosition().y
			+ ((float)b->dna.collisionRadius * b->dna.size / 2));

		float distance = std::sqrt((dx * dx) + (dy * dy));

		if (distance <= ((float)a->dna.collisionRadius * a->dna.size) + ((float)b->dna.collisionRadius * b->dna.size)
			&& a->canCreateChild(*b)) {
			auto child = Entity(*a, *b);
			entities.push_back(child);

			childrenAmount++;

			a->dna.reproductionRate += a->dna.reproductionRate;
			b->dna.currentLifeTime += b->dna.reproductionRate;
		}
	}
}