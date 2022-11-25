#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{

public:

	BuoyancyForceGenerator(float h, float a, float b, float c, float d);
	virtual void updateForce(Particle *p, double t);
	
protected:
	float height;
	float volume;
	float liquidDensity;
	float gravity = 9.8;

	Particle* liquidParticle;
};

