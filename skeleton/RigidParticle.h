#pragma once
#include <PxPhysicsAPI.h>
#include <iostream>
#include <string>
#include "RenderUtils.hpp"
#include "core.hpp"
#include "RigidParticlesNames.h"
#include "ParticleSys.h"

using namespace physx;
using namespace std;

class RigidParticle
{
	
public:

	RigidParticle(PxRigidDynamic *solid_, double tiempoVida_, bool destroyable, RenderItem *item_);
	RigidParticle(PxRigidStatic *solid_, bool destroyable, RenderItem *item_);
	virtual ~RigidParticle();

	virtual void integrate(double t);
	bool viva();
	void setAlive(bool state);
	virtual void onCollision(names mn, ParticleSys *pSys) {};

	PxActor* getActor();
	PxRigidDynamic* getDynamicP();
	PxRigidStatic* getStaticP();
	string getName();
	void setTypeName(names nm);
	names getTypeName();

private:

	PxRigidDynamic* solidDynamic = nullptr;
	PxRigidStatic* solidStatic = nullptr;
	RenderItem *item;

	names name;
	
	double tiempoVida;

	bool alive;
	bool destroyable;

};

