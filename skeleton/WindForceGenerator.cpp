#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const float& k1_, const float& k2_, Vector3 windF_)
{
	k1 = k1_;
	k2 = k2_;
	windF = windF_;
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getProperties().inv_mass) < 1e-10) {
		return;
	}

	if(k2 == 0){
		k2 = airDensity*cD*particle->getProperties().radius*4*pi;
	}

	Vector3 dragF;

	Vector3  resta = particle->getProperties().vel - windF;

	float drag_coef = resta.normalize();

	drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;

	dragF = -resta * drag_coef;

	particle->addForce(dragF);
}
