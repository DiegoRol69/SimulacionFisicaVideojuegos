#pragma once

#include "RigidParticle.h"
#include <list>
#include <random>
#include <cmath>

class RigidForceGenerator
{
public:
	virtual void updateForce(RigidParticle* rigidParticle, double duration) = 0;
	std::string _name;
	double t = -1e10;
	double const pi = 3.1415926535;
};

