#pragma once

#include "Particle.h"
#include <list>
#include <random>
#include <cmath>

class ForceGenerator
{
public:
	virtual void updateForce(Particle *particle, double duration) = 0;
	std::string _name;
	double t = -1e10;
	double const pi = 3.1415926535;
};

