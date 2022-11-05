#pragma once
#include "ParticleGenerator.h"
#include "FireWork.h"

class UniformParticleGen:public ParticleGenerator
{

	Vector3 vel_width, pos_width;

	typeF tipoF;

	std::uniform_real_distribution<> px;
	std::uniform_real_distribution<> py;
	std::uniform_real_distribution<> pz;

	std::uniform_real_distribution<> vx;
	std::uniform_real_distribution<> vy;
	std::uniform_real_distribution<> vz;

public:

	UniformParticleGen(Particle *p, int n, double _generation_probability_, 
		Vector3 pos_width_, Vector3 vel_width_, typeF tipoF_);

	~UniformParticleGen() {};

	std::list<Particle*> generateParticles() override;
	void setDistribution() override;
	void setForceToClon() override;
	ForceGenerator *getTypeF() override;
};

