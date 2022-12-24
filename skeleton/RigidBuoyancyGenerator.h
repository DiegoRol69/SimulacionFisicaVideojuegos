#pragma once
#include "RigidForceGenerator.h"
#include "Particle.h"
#include "core.hpp"

class RigidBuoyancyGenerator : public RigidForceGenerator
{

public:

	RigidBuoyancyGenerator(float h, float d);
	virtual void updateForce(RigidParticle* p, double t);
	void setVolume(float r);

protected:
	float height;
	float volume;
	float liquidDensity;
	float gravity = 9.8;

	Particle* liquidParticle;
};

