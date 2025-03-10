#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k_, double restingLength_, Particle* other_)
{
	k = k_;
	restingLength = restingLength_;
	other = other_;
}

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 force = other->getProperties().pose.p - particle->getProperties().pose.p;

	const float length = force.normalize();
	const float delta_x = length - restingLength;

	if (length > restingLength) {
		force *= delta_x * k;
		particle->addForce(force);
	}

}

void SpringForceGenerator::setK(double k_)
{
	k += k_;
}
