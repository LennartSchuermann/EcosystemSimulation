#include "DNASystem.h"

char genGender() {
	auto gVal = (int)genRandomNumber(0, 2);
	if (gVal == 0) {
		return 'm';
	}
	return 'f';
}

dna CreateDNA() {
	auto createdDna = dna();

	//create random dna
	createdDna.gender = genGender();

	createdDna.size = genRandomNumber(2, 15);
	createdDna.speed = genRandomNumber(1, 5);

	createdDna.maxAge = (int)genRandomNumber(15, 80) * 100;				//btw 2.5 & 13 sec lifetime
	createdDna.reproductionRate = (int)genRandomNumber(15, 50) * 10;	//btw every 2.5 & 8 sec
	createdDna.collisionRadius = (int)genRandomNumber(1, 5);

	createdDna.color = createRandomRgb();

	return createdDna;
}

dna GenerateDNA(const dna *mother, const dna *father) {
	auto childDna = dna();

	//gen as child
	childDna.gender = genGender();

	childDna.size = (mother->size + father->size) / 2;
	childDna.speed = (mother->speed + father->speed) / 2;

	childDna.maxAge = (mother->maxAge + father->maxAge) / 2;
	childDna.reproductionRate = (mother->reproductionRate + father->reproductionRate) / 2;
	childDna.collisionRadius = (mother->collisionRadius + father->collisionRadius) / 2;

	childDna.color = mix2Colors(mother->color, father->color);
	
	return childDna;
}