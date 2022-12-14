#include "RigidExplosion.h"

RigidExplosion::RigidExplosion(double K_, double R_, double constExplosion_, Vector3 explosionPos_)
{
	K = K_;
	explosionPos = explosionPos_;
	R = R_;
	constExplosion = constExplosion_;
}

void RigidExplosion::updateForce(RigidParticle* particle, double t)
{

	Vector3 particlePos = particle->getDynamicP()->getGlobalPose().p;
	Vector3 explosionDir = { 0,0,0 };
	Vector3 explosionF;

	double r = pow((particlePos.x - explosionPos.x), 2) + pow((particlePos.y - explosionPos.y), 2)
		+ pow((particlePos.z - explosionPos.z), 2);

	r = sqrt(r);

	if (r < R) {

		double a = K / pow(r, 2);
		double b = pow(e, -(t / constExplosion));

		explosionDir = a * Vector3(particlePos.x - explosionPos.x, particlePos.y - explosionPos.y, particlePos.z - explosionPos.z) * b;
	}

	particle->getDynamicP()->addForce(explosionDir, PxForceMode::eFORCE);
}

void RigidExplosion::addConst(double t)
{
	constExplosion += t;
	R = vE * t * 100;
}
