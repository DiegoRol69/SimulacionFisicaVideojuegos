#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "FireWork.h"
#include "ParticleForceRegistry.h"

enum TipoGen {Gaussian, Uniform, Circle};

class ParticleSys
{

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGen;
	std::list<ForceGenerator*> forceGen;
	std::vector<FireWork*> firework_pool;
	ParticleForceRegistry *FR;

	Vector3 max_pos;
	Vector3 min_pos;

public:

	ParticleSys();
	~ParticleSys() {};

	void update( double t);
	void addGen(TipoGen tipo);

	void shootFirework(int type);
	void generateFireworkSystem();
};

