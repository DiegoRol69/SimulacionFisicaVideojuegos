#pragma once
#include "core.hpp"
#include "WindForceGenerator.h"

class Whirlwind : public WindForceGenerator
{

	int K;
	Vector3 whirlPos;

public:

	Whirlwind(double K_, Vector3 whirlPos_);
	virtual void updateForce(Particle* particle, double t);

};

