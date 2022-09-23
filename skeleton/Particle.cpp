#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	vel = v;
	damping = damp;
	aceleration = acel;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, {1, 0, 0, 1});

	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + (vel * t);
	vel = vel * (pow(damping, t)) + aceleration * t;
}
