#include "RigidBuoyancyGenerator.h"

RigidBuoyancyGenerator::RigidBuoyancyGenerator(float h, float d)
{
	height = h;
	liquidDensity = d;

	liquidParticle = new Particle();

	liquidParticle->setParticle(Vector3(0, 10, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 10,
		CreateShape(physx::PxBoxGeometry(20, 1, 20)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), false, false, 2);
}

void RigidBuoyancyGenerator::updateForce(RigidParticle* p, double t)
{
	float h = p->getDynamicP()->getGlobalPose().p.y;
	float h0 = liquidParticle->getProperties().pose.p.y;

	Vector3 f(0, 0, 0);
	float immersed = 0;

	if (h - h0 > height * 0.5) { immersed = 0.0; }
	else if (h0 - h > height * 0.5) { immersed = 1.0; }
	else { immersed = (h0 - h) / height + 0.5; }

	f.y = liquidDensity * volume * immersed;

	p->getDynamicP()->addForce(f);
}

void RigidBuoyancyGenerator::setVolume(float r)
{
	volume = (4 / 3) * pi * pow(r, 3);
}
