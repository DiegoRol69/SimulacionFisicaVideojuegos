#include "AtractionForce.h"
#include <iostream>

AtractionForce::AtractionForce(double K_, Vector3 atractionPos_)
{
	K = K_;
	atractionPos = atractionPos_;
}

void AtractionForce::updateForce(RigidParticle* particle, double t)
{
	Vector3 particlePos = particle->getDynamicP()->getGlobalPose().p;
	Vector3 fDir = K * ( atractionPos - particlePos);

	particle->getDynamicP()->addForce(fDir);
}
