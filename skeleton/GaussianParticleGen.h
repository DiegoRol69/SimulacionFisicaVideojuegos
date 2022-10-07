#pragma once
#include "ParticleGenerator.h"
#include "Particle.h"
#include <random>

class GaussianParticleGen : public ParticleGenerator
{

	Vector3 dev_pos, dev_vel;
	double dev_t;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

public:

	GaussianParticleGen(Vector3 pos, Vector3 vel, int n, Vector3 dev_pos_, Vector3 dev_vel_, double _generation_probability_,  
		double dev_t_, double mean_t_);
	~GaussianParticleGen() {};

	 std::list<Particle*> generateParticles() override;
};

