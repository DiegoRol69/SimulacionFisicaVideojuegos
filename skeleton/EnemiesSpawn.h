#pragma once

#pragma once
#pragma once
#include "ParticleRigidGenerator.h"

class EnemiesSpawn :public ParticleRigidGenerator
{
	double dev_t;
	double r;

public:

	EnemiesSpawn(PxShape* shape_, double r_, names name_, int n, double _generation_probability_,
		double dev_t_, double mean_t_);
	~EnemiesSpawn() {};

	std::list<RigidParticle*> generateParticles(PxPhysics* gPhysics) override;
	void setDistribution() override {};

};

