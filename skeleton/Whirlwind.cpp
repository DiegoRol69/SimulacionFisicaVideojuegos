#include "Whirlwind.h"

Whirlwind::Whirlwind(double K_, Vector3 whirlPos_) : WindForceGenerator(0.8, 0.0, {0,0,0})
{
	K = K_;
	whirlPos = whirlPos_;
}

void Whirlwind::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getProperties().inv_mass) < 1e-10) {
		return;
	}

	Vector3 dragF;
	Vector3 particlePos = particle->getProperties().pose.p;

	Vector3 vWhirl(-(particlePos.z - whirlPos.z), 50 - (particlePos.y - whirlPos.y), particlePos.x - whirlPos.x);

	vWhirl *= K;

	Vector3  resta = vWhirl - particle->getProperties().vel;

	float drag_coef = resta.normalize();

	drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;

	dragF = -resta * drag_coef;

	particle->addForce(dragF);
}
