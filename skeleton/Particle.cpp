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

void Particle::setParticle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, physx::PxShape* shape, 
	double tiempoVida_, Vector3 center_, Vector3 maxRange_, bool prefab, bool compruebaRango_)
{
	properties.pose = physx::PxTransform(pos.x, pos.y, pos.z);
	properties.vel = v;
	properties.damping = damp;
	properties.aceleration = acel;
	properties.masa = m;
	properties.shape = shape;
	properties.tiempoVida = tiempoVida_;
	properties.center = center_;
	properties.maxRange = maxRange_;
	properties.compruebaRango = compruebaRango_;

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
	bool inRange = true;

	if (properties.compruebaRango) {
		inRange = properties.pose.p.x < properties.center.x + properties.maxRange.x && properties.pose.p.x > properties.center.x - properties.maxRange.x &&
			properties.pose.p.y < properties.center.y + properties.maxRange.y && properties.pose.p.y > properties.center.y - properties.maxRange.y &&
			properties.pose.p.z < properties.center.z + properties.maxRange.z && properties.pose.p.z > properties.center.z - properties.maxRange.z;
	}

	return properties.tiempoVida > 0 && inRange;
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
	properties.center = pModel.center;
	properties.maxRange = pModel.maxRange;
	properties.compruebaRango = pModel.compruebaRango;

	std::uniform_real_distribution<double> color(0, 1);

	properties.renderItem = new RenderItem(properties.shape, &properties.pose, { float(color(gen)), float(color(gen)), float(color(gen)), 1 });
}

particleProperties Particle::getProperties()
{
	return properties;
}




