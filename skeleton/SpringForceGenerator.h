#pragma once
#include "core.hpp"
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{

public:
	SpringForceGenerator(double k_, double restingLength_, Particle *other_);
	~SpringForceGenerator() {};
	virtual void updateForce(Particle *particle, double t);
	void setK(double k_);

protected:
	double k;
	double restingLength;
	double longMin;
	Particle* other;
};

