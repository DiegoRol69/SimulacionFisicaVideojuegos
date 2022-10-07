#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"

enum TipoGen {Gaussian, Uniform};

class ParticleSys
{

	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGen;

	Vector3 max_pos;
	Vector3 min_pos;

public:

	ParticleSys(int n);
	~ParticleSys() {};

	void update( double t);

};

