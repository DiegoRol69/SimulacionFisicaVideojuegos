#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float a, float b, float c, float d)
{
	height = h;
	volume = a*b*c;
	liquidDensity = d;

	liquidParticle = new Particle();

	liquidParticle->setParticle(Vector3(20, 30, 20), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 10,
		CreateShape(physx::PxBoxGeometry(a, b, c)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, 2);
}

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	float h = p->getProperties().pose.p.y;
	float h0 = liquidParticle->getProperties().pose.p.y;

	Vector3 f(0,0,0);
	float immersed = 0;

	if (h - h0 > height * 0.5) { immersed = 0.0; }
	else if (h0 - h > height * 0.5) { immersed = 1.0; }
	else { immersed = (h0 - h) / height + 0.5; }

	f.y = liquidDensity * volume * immersed;

	p->addForce(f);
}
