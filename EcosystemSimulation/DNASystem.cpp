#include "ColorManager.h"

using dna = struct {
	char gender;    //"m" = male, "f" = female

	float size;
	float speed;

	int maxAge;				//time in frames * 10
	int reproductionRate;
	int collisionRadius;

	rgb color;
};

char genGender() {
	auto gVal = (int)genRandomNumber(0, 2);
	if (gVal == 0) {
		return 'm';
	}
	return 'f';
}

dna CreateDNA() {
	dna createdDna;

	//create random dna
	createdDna.gender = genGender();

	createdDna.size = genRandomNumber(2, 15);
	createdDna.speed = genRandomNumber(1, 5);

	createdDna.maxAge = (int)genRandomNumber(15, 80) * 10;				//btw 2.5 & 13 sec lifetime
	createdDna.reproductionRate = (int)genRandomNumber(15, 50) * 10;	//btw every 2.5 & 8 sec
	createdDna.collisionRadius = (int)genRandomNumber(1, 5);

	createdDna.color = createRandomRgb();

	return createdDna;
}

dna GenerateDNA(const dna *mother, const dna *father) {
	dna childDna;

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