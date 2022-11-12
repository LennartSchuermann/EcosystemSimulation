#pragma once
#include "ColorManager.h"

using dna = struct {
	char gender;    //"m" = male, "f" = female

	float size;
	float speed;

	int currentLifeTime;
	int maxAge;				//time in frames * 10
	int reproductionRate;
	int collisionRadius;

	rgb color;
};

inline char genGender();

dna CreateDNA();

dna GenerateDNA(const dna* mother, const dna* father);