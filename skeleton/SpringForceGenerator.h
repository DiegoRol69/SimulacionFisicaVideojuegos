#pragma once

#include "core.hpp"
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{

public:
	SpringForceGenerator(double k_, double restingLength_, Particle *other_);
	virtual void updateForce(Particle *particle);
	inline void setK(double k_) { k = k_; };

protected:
	double k;
	double restingLength;
	Particle* other;
};

