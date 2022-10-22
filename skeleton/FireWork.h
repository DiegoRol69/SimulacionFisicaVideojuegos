#pragma once
#include <memory>
#include "ParticleGenerator.h"
#include <list>
#include "Particle.h"

using namespace std;

class FireWork:public Particle
{

	list<shared_ptr <ParticleGenerator>> _gens;

public:

	FireWork();
	~FireWork() {};
	int update(double t);

	virtual Particle* clone() const;
	list<Particle*> explode();

};

