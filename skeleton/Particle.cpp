#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double tiempoVida_)
{
	properties.pose = physx::PxTransform(pos.x, pos.y, pos.z);
	properties.vel = v;
	properties.damping = damp;
	properties.aceleration = acel;
	properties.tiempoVida = tiempoVida_;

	properties.renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &properties.pose, {1, 1, 0, 1});

}

void Particle::setParticle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, physx::PxShape* shape, double tiempoVida_, bool prefab)
{
	properties.pose = physx::PxTransform(pos.x, pos.y, pos.z);
	properties.vel = v;
	properties.damping = damp;
	properties.aceleration = acel;
	properties.masa = m;
	properties.shape = shape;
	properties.tiempoVida = tiempoVida_;

	if (prefab) {
		properties.renderItem = new RenderItem(shape, &properties.pose, { 1, 0, 0, 1 });
	}

	else properties.renderItem = nullptr;

	//RegisterRenderItem(properties.renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(properties.renderItem);
}

void Particle::integrate(double t)
{
	properties.pose.p = properties.pose.p + (properties.vel * t);
	properties.vel = properties.vel * (pow(properties.damping, t)) + properties.aceleration * t;

	properties.tiempoVida -= t;
}

bool Particle::viva()
{
	return properties.tiempoVida > 0;
}

Particle* Particle::clone()
{
	Particle* p = new Particle();
	p->copyParticle(this);
	return p;
}


void Particle::setTime(double time) {
	properties.tiempoVida = time;
}

void Particle::setPos(Vector3 pos) {
	properties.pose = physx::PxTransform(pos.x, pos.y, pos.z);
}

void Particle::setVel(Vector3 vel)
{
	properties.vel = vel;
}

void Particle::copyParticle(Particle* p)
{
	particleProperties pModel = p->getProperties();

	properties.pose = physx::PxTransform(pModel.pose.p.x, pModel.pose.p.y, pModel.pose.p.z);
	properties.vel = pModel.vel;
	properties.damping = pModel.damping;
	properties.aceleration = pModel.aceleration;
	properties.masa = pModel.masa;
	properties.shape = pModel.shape;
	properties.tiempoVida = pModel.tiempoVida;

	properties.renderItem = new RenderItem(pModel.shape, &properties.pose, { 1, 1, 0, 1 });
}

particleProperties Particle::getProperties()
{
	return properties;
}




