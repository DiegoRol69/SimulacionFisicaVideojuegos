#include "RigidParticle.h"

RigidParticle::RigidParticle(PxRigidDynamic *solid_, double tiempoVida_, RenderItem *item_)
{
	tiempoVida = tiempoVida_;
	solid = solid_;
	item = item_;
	alive = true;
}

void RigidParticle::integrate(double t)
{
	if (alive) {
		tiempoVida -= t;
		if (tiempoVida < 0) alive = false;
	}
}

bool RigidParticle::viva()
{
	return alive;
}

void RigidParticle::setAlive(bool state)
{
	alive = state;
}

PxRigidActor* RigidParticle::getActor()
{
	return solid;
}

PxRigidDynamic *RigidParticle::getDynamicP()
{
	return solid;
}

string RigidParticle::getName()
{
	return solid->getName();
}

RigidParticle::~RigidParticle()
{
	DeregisterRenderItem(item);
}
