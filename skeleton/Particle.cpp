#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double tiempoVida_)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	vel = v;
	damping = damp;
	aceleration = acel;
	tiempoVida = tiempoVida_;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, {1, 1, 0, 1});

	RegisterRenderItem(renderItem);
}

void Particle::setProyectile(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, physx::PxShape* shape)
{
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	vel = v;
	damping = damp;
	aceleration = acel;
	masa = m;

	renderItem = new RenderItem(shape, &pose, { 1, 0, 0, 1 });

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

	tiempoVida -= t;
}

bool Particle::viva()
{
	return tiempoVida > 0;
}


