#include "ColorManager.h"
#include "Entity.h"

struct dna{};
typedef struct NamedType : dna {
	char gender;    //"m" = male, "f" = female

	float size;
	float speed;

	int maxAge;				//time in frames * 10
	int reproductionRate;
	int collisionRadius;

	rgb color;

	char genGender() {
		int gVal = (int)genRandomNumber(0, 2);
		if (gVal == 0) {
			return 'm';
		}
		return 'f';
	}

	void CreateDNA() {
		//create random dna
		gender = genGender();

		size = genRandomNumber(2, 15);
		speed = genRandomNumber(1, 5);

		maxAge = (int)genRandomNumber(15, 80) * 10;				//btw 2.5 & 13 sec lifetime
		reproductionRate = (int)genRandomNumber(15, 50) * 10;	//btw every 2.5 & 8 sec
		collisionRadius = (int)genRandomNumber(1, 5);

		color = createRandomRgb();
	}
} dna;


//TODO FIX
dna GenerateDNA(Entity mother, Entity father) {
	dna childDna;

	//gen as child
	childDna.gender = childDna.genGender();

	childDna.size = (mother.dna.size + father.dna.size) / 2;
	childDna.speed = (mother.dna.speed + father.dna.speed) / 2;

	childDna.maxAge = (mother.dna.maxAge + father.dna.maxAge) / 2;
	childDna.reproductionRate = (mother.dna.reproductionRate + father.dna.reproductionRate) / 2;
	childDna.collisionRadius = (mother.dna.collisionRadius + father.dna.collisionRadius) / 2;

	childDna.color = mix2Colors(mother.dna.color, father.dna.color);
}