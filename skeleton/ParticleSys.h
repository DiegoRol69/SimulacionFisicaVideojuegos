#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "FireWork.h"

enum TipoGen {Gaussian, Uniform};

class ParticleSys
{

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGen;
	std::vector<FireWork*> _firework_pool;
	ParticleGenerator* _firework_gen;

	Vector3 max_pos;
	Vector3 min_pos;

public:

	ParticleSys();
	~ParticleSys() {};

	void update( double t);
	void addGen(TipoGen tipo);

	void shootFirework(int type);
	void onParticleDeath(Particle * particle);
	void generateFireworkSystem();
};

