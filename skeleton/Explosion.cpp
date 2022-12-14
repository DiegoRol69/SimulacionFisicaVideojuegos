#include "Explosion.h"
#include <iostream>

Explosion::Explosion(double K_, double R_, double constExplosion_ ,Vector3 explosionPos_)
{
	K = K_;
	explosionPos = explosionPos_;
	R = R_;
	constExplosion = constExplosion_;
}

void Explosion::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getProperties().inv_mass) < 1e-10) {
		return;
	}

	Vector3 particlePos = particle->getProperties().pose.p;
	Vector3 explosionDir = {0,0,0};
	Vector3 explosionF;

	double r = pow((particlePos.x - explosionPos.x), 2) + pow((particlePos.y - explosionPos.y), 2)
		+ pow((particlePos.z - explosionPos.z), 2);

	r = sqrt(r);

	if (r < R) {

		double a = K / pow(r, 2);
		double b = pow(e, -(t / constExplosion));

		explosionDir = a* Vector3(particlePos.x - explosionPos.x, particlePos.y - explosionPos.y, particlePos.z - explosionPos.z) * b;
	}

	particle->addForce(explosionDir * particle->getProperties().masa);
}

void Explosion::addConst(double t)
{
	constExplosion += t;
	R = vE * t*100;
}
