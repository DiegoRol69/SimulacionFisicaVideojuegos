#pragma once
#include <list>
#include "Particle.h"
#include "FireWork.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "TipoGenerador.h"

class ParticleSys
{

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGen;
	std::list<ForceGenerator*> forceGen;
	std::vector<FireWork*> firework_pool;

	ParticleForceRegistry *FR;
	WindForceGenerator * wind;
	SpringForceGenerator* fsp1 = nullptr;
	SpringForceGenerator* fsp2 = nullptr;
	AnchoredSpringForceGenerator* fanch = nullptr;
	GravityForceGenerator* gf;
	Explosion* explosion;
	
	Particle* muelle1;
	Particle* muelle2;

	Vector3 max_pos;
	Vector3 min_pos;

	bool explosionActive;

public:

	ParticleSys();
	~ParticleSys() {};

	void update( double t);

	void addGen(TipoGen tipo);
	void addGenInPos(TipoGen tipo, Vector3 pos);
	void addParticle();
	void addExplosion();
	void addWind();
	void addGravity();
	void addK();

	void quitRegistry();
	void deleteGenerators();

	void shootFirework(int type);
	void generateFireworkSystem();
	void generateFireworkInPos(Vector3 pos);
	void Spring();
	void Anchored();
	void Slinky();
	void Buoyancy();
};

