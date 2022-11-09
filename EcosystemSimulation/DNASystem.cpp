#include "ColorManager.h"


struct Dna{};
typedef struct NamedType : Dna {
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

		maxAge = genRandomNumber(15, 80) * 10;				//btw 2.5 & 13 sec lifetime
		reproductionRate = genRandomNumber(15, 50) * 10;	//btw every 2.5 & 8 sec
		collisionRadius = genRandomNumber(1, 5);

		color = createRandomRgb();
	}

	void generateDNA() {
		//gen as child

		//rgb mix = mix2Colors({ 237, 235, 78 }, { 235, 64, 52 });
	}
} dna;