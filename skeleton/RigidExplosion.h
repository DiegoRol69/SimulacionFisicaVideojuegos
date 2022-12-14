#pragma once
#include "RigidForceGenerator.h"

class RigidExplosion:public RigidForceGenerator
{
	double const e = 2.71828182845904525356;
	double vE = 343.55489;
	double K, R, constExplosion;
	Vector3 explosionPos;

public:

	RigidExplosion(double K_, double R_, double constExplosion_, Vector3 explosionPos_);
	virtual void updateForce(RigidParticle* particle, double t);
	void addConst(double t);
};

