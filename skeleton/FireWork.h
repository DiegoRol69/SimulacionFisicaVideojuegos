#pragma once
#include <memory>
#include "ParticleGenerator.h"
#include <list>
#include "Particle.h"

using namespace std;

class FireWork:public Particle
{

	list<shared_ptr <ParticleGenerator>> _gens;
	int div;
	int divTotales;

public:

	FireWork();
	~FireWork() {};

	void setFireWork(FireWork *p);
	void setFireWork(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, physx::PxShape* shape, 
		double tiempoVida_, int nDiv, int nGen, shared_ptr <ParticleGenerator> gen);

	list<Particle*> explode();
	list<shared_ptr <ParticleGenerator>> getGens() { return _gens; };
};

