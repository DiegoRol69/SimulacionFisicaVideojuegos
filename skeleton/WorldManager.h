#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RigidParticle.h"
#include <list>

using namespace physx;
using namespace std;

class WorldManager
{

public:
	
	WorldManager(PxScene* gScene_, PxPhysics* gPhysics_);
	~WorldManager();

	void createRigidDynamic(Vector3 pos, Vector3 vel, PxShape *shape, double density, Vector4 color, char *name);
	void collisionEfect(PxActor * actor1, PxActor* actor2);

	void update(double t);

private:

	PxScene* gScene;
	PxPhysics* gPhysics;
	RenderItem* item;
	list<RigidParticle*> rigidParticles;

};

