#pragma once
#include "core.hpp"
#include "RigidForceGenerator.h"

class AtractionForce : public RigidForceGenerator
{

	double K;
	Vector3 atractionPos;

public:

	AtractionForce(double K_, Vector3 atractionPos_);
	virtual void updateForce(RigidParticle* particle, double t);
};

