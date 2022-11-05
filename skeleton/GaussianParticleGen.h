#pragma once
#include "ParticleGenerator.h"
#include "FireWork.h"

class GaussianParticleGen : public ParticleGenerator
{

	Vector3 dev_pos, dev_vel;
	double dev_t;
	Particle* particle;

	std::normal_distribution<> px;
	std::normal_distribution<> py;
	std::normal_distribution<> pz;

	std::normal_distribution<> vx;
	std::normal_distribution<> vy;
	std::normal_distribution<> vz;

public:

	GaussianParticleGen(Particle *p, int n, Vector3 dev_pos_, Vector3 dev_vel_, 
		double _generation_probability_, double dev_t_, typeF tipoF_);

	~GaussianParticleGen() {};

	 std::list<Particle*> generateParticles() override;
	 void setDistribution() override;
	 void setForceToClon() override;
	 ForceGenerator *getTypeF() override;
};

