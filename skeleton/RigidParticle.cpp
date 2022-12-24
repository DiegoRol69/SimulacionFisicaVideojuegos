#include "RigidParticle.h"

RigidParticle::RigidParticle(PxRigidDynamic* solid_, double tiempoVida_, bool destroyable_, RenderItem* item_)
{
	tiempoVida = tiempoVida_;
	destroyable = destroyable_;
	solidDynamic = solid_;
	item = item_;
	alive = true;
}

RigidParticle::RigidParticle(PxRigidStatic* solid_, bool destroyable_, RenderItem* item_)
{
	destroyable = destroyable_;
	solidStatic = solid_;
	item = item_;
	alive = true;
}

void RigidParticle::integrate(double t)
{
	if (alive && destroyable) {
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

void RigidParticle::activeDestroyable()
{
	destroyable = true;
}

PxActor* RigidParticle::getActor()
{
	if (solidDynamic != nullptr) return solidDynamic;
	else return solidStatic;
}

PxRigidDynamic* RigidParticle::getDynamicP()
{
	return solidDynamic;
}

PxRigidStatic* RigidParticle::getStaticP()
{
	return solidStatic;
}

string RigidParticle::getName()
{
	string name;

	if (solidDynamic != nullptr) name = solidDynamic->getName();
	else name = solidStatic->getName();

	return name;
}

void RigidParticle::setTypeName(names nm)
{
	name = nm;
}

names RigidParticle::getTypeName()
{
	return name;
}

RigidParticle::~RigidParticle()
{
	if (item != nullptr) {
		DeregisterRenderItem(item);
	}
}
