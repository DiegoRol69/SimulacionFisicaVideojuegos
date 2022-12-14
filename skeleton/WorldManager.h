#pragma once
#include <PxPhysicsAPI.h>
#include <list>
#include <random>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RigidParticle.h"
#include "ParticleRigidGenerator.h"
#include "NormalParticleRigidGenerator.h"
#include "RigidParticleForceRegistry.h"
#include "RigidForceGenerator.h"
#include "RigidExplosion.h"
#include "TipoFuerzas.h"
#include "TipoGenerador.h"
#include "RigidParticlesNamesManager.h"
#include "Enemy.h"

using namespace physx;
using namespace std;

class WorldManager
{

public:

	WorldManager(PxScene* gScene_, PxPhysics* gPhysics_);
	~WorldManager();

	void createRigidDynamic(Vector3 pos, Vector3 vel, PxShape* shape, double density,
		Vector4 color, names nm, double mass);
	void collisionEfect(PxActor* actor1, PxActor* actor2);
	void addGen(TipoGen tipoGen, names nm);
	void addForce(typeF tipoF);
	void update(double t);
	void deleteGenerators();

private:

	PxScene* gScene;
	PxPhysics* gPhysics;
	RenderItem* item;
	list<RigidParticle*> rigidParticles;
	list<ParticleRigidGenerator*> particleGen;

	double genTime;
	double contTimeGen;

	RigidExplosion* rExplosion = nullptr;

	RigidParticleForceRegistry* RFR;
	RigidParticlesNamesManager* NM;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

};

