#include "ParticleDragGenerator.h"

ParticleDragGenerator::ParticleDragGenerator(const float k1_, const float k2_)
{
	k1 = k1_;
	k2 = k2_;
}

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getProperties().inv_mass) < 1e-10) {
		return;
	}
	Vector3 dragF;

	Vector3  v = particle->getProperties().vel;

	float drag_coef = v.normalize();

	drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;

	dragF = -v * drag_coef;

	particle->addForce(dragF);
}
