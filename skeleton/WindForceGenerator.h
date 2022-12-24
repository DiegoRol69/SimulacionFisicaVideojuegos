#pragma once
#include "ParticleDragGenerator.h"
#include "core.hpp"

class WindForceGenerator : public ParticleDragGenerator
{

public:

	WindForceGenerator() {};
	WindForceGenerator(const float& k1_, const float& k2_, Vector3 windF_);

	virtual void updateForce(Particle* particle, double t);

	inline void setDrag(float k1_, float& k2_) { k1 = k1_; k2 = k2_; }

protected:
	float k1, k2;
	double const cD = 0.5;
	double const airDensity = 1.20;
	Vector3 windF;
};
