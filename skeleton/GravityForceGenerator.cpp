#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
	_gravity = g;
}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getProperties().inv_mass) < 1e-10) {
		return;
	}

	particle->addForce(_gravity*particle->getProperties().masa);
}
