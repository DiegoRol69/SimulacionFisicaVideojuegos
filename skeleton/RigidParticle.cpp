#include "RigidParticle.h"

RigidParticle::RigidParticle(PxRigidDynamic *solid_, double tiempoVida_, RenderItem *item_)
{
	tiempoVida = tiempoVida_;
	solid = solid_;
	item = item_;
	alive = true;
}

RigidParticle::~RigidParticle()
{
	DeregisterRenderItem(item);
}

bool RigidParticle::viva()
{
	return alive;
}

void RigidParticle::setAlive(bool state)
{
	alive = state;
}

PxRigidActor *RigidParticle::getActor()
{
	return solid;
}

void RigidParticle::integrate(double t)
{
	std::cout << tiempoVida << "\n";
	if (alive) {
		tiempoVida -= t;
		if (tiempoVida < 0) alive = false;
	}
}

string RigidParticle::getName()
{
	return solid->getName();
}
