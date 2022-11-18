#pragma once
#include "core.hpp"
#include "ForceGenerator.h"

class Explosion : public ForceGenerator
{
	double const e = 2.71828182845904525356;
	double vE = 343.55489;
	double K, R, constExplosion;
	Vector3 explosionPos;

public:

	Explosion(double K_, double R_, double constExplosion,Vector3 explosionPos_);
	virtual void updateForce(Particle* particle, double t);
	void addConst(double t);

};

