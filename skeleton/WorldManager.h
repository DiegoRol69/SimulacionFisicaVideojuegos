#pragma once
#include <PxPhysicsAPI.h>
#include <list>
#include <random>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RigidParticle.h"
#include "ParticleRigidGenerator.h"
#include "NormalParticleRigidGenerator.h"
#include "EnemiesSpawn.h"
#include "RigidParticleForceRegistry.h"
#include "RigidForceGenerator.h"
#include "RigidExplosion.h"
#include "AtractionForce.h"
#include "RigidBuoyancyGenerator.h"
#include "TipoFuerzas.h"
#include "TipoGenerador.h"
#include "RigidParticlesNamesManager.h"
#include "Enemy.h"
#include "ParticleSys.h"
#include "Proyectile.h"

using namespace physx;
using namespace std;

class WorldManager
{

public:

	WorldManager(PxScene* gScene_, PxPhysics* gPhysics_, ParticleSys* pSys_);
	~WorldManager();

	void collisionEfect(PxActor* actor1, PxActor* actor2);
	void addGen(TipoGen tipoGen, names nm);
	void addForce(typeF tipoF);
	void addForceInPos(typeF tipoF, Vector3 pos);
	void shootProyectile(Vector3 pos, Vector3 vel, PxShape* shape, double density,
		Vector4 color, names nm);
	void update(double t);
	void deleteGenerators();

private:

	PxScene* gScene;
	PxPhysics* gPhysics;
	RenderItem* item;
	ParticleSys* pSys;
	list<RigidParticle*> rigidParticles;
	list<ParticleRigidGenerator*> particleGen;

	double genTime;
	double contTimeGen;
	double contTimeReset;
	double resetTime;
	bool atractionActive = false;
	int minSize;

	RigidExplosion* rExplosion = nullptr;
	RigidBuoyancyGenerator* rBuoyancy = nullptr;

	RigidParticleForceRegistry* RFR;
	RigidParticlesNamesManager* NM;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

};

