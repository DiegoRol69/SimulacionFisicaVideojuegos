#pragma once
#include "ParticleGenerator.h"

class UniformParticleGen:public ParticleGenerator
{

	Vector3 vel_width, pos_width;

	std::uniform_real_distribution<> px;
	std::uniform_real_distribution<> py;
	std::uniform_real_distribution<> pz;

	std::uniform_real_distribution <> vx;
	std::uniform_real_distribution<> vy;
	std::uniform_real_distribution<> vz;

public:

	UniformParticleGen(Vector3 pos, Vector3 vel, int n,  double _generation_probability_, Vector3 pos_width_, Vector3 vel_width_);
	~UniformParticleGen() {};

	std::list<Particle*> generateParticles() override;

};

