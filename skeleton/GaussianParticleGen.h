#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGen : public ParticleGenerator
{

	Vector3 dev_pos, dev_vel;
	double dev_t;

	std::normal_distribution<> px;
	std::normal_distribution<> py;
	std::normal_distribution<> pz;

	std::normal_distribution<> vx;
	std::normal_distribution<> vy;
	std::normal_distribution<> vz;

public:

	GaussianParticleGen(Vector3 pos, Vector3 vel, int n, Vector3 dev_pos_, Vector3 dev_vel_, double _generation_probability_,  
		double dev_t_, double mean_t_);
	~GaussianParticleGen() {};

	 std::list<Particle*> generateParticles() override;
};

