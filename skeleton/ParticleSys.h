#pragma once
#include <list>
#include "Particle.h"
#include "FireWork.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "ParticleDragGenerator.h"

enum TipoGen {Gaussian, Uniform, Circle};

class ParticleSys
{

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGen;
	std::list<ForceGenerator*> forceGen;
	std::vector<FireWork*> firework_pool;

	ParticleForceRegistry *FR;
	WindForceGenerator * wind;
	SpringForceGenerator* fsp1;
	SpringForceGenerator* fsp2;
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
	void addParticle();
	void addExplosion();
	void addWind();
	void addGravity();
	void addK();

	void quitRegistry();

	void shootFirework(int type);
	void generateFireworkSystem();
	void Spring();
	void Anchored();
	void Slinky();
	void Buoyancy();
};

