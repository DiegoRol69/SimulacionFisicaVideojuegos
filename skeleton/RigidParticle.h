#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <iostream>
#include <string>

using namespace physx;
using namespace std;

class RigidParticle
{
	
public:

	RigidParticle(PxRigidDynamic *solid_, double tiempoVida_, RenderItem *item_);
	~RigidParticle();

	PxRigidActor* getActor();
	PxRigidDynamic *getDynamicP();

	bool viva();
	void setAlive(bool state);
	virtual void integrate(double t);
	string getName();

private:

	PxRigidDynamic* solid;
	double tiempoVida;
	RenderItem *item;
	bool alive;

};

