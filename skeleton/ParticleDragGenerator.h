#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class ParticleDragGenerator : public ForceGenerator
{

public:

	ParticleDragGenerator(){};
	ParticleDragGenerator(const float k1_, const float k2_);
	virtual void updateForce(Particle *particle, double t);
	inline void setDrag(float k1_, float k2_) { k1 = k1_;  k2 = k2_; };
	inline float getK1() { return k1; };
	inline float getK2() { return k2; };

private:
	float k1, k2;
};

