#pragma once
#include <random>

inline float genRandomNumber(float min, float max) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_real_distribution<> distr(min, max); // define the range

	return (float)distr(gen);
}