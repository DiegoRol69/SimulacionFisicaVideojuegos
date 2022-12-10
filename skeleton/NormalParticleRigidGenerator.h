#pragma once
#pragma once
#include "ParticleRigidGenerator.h"

#define MAX_P 100

class NormalParticleRigidGenerator :public ParticleRigidGenerator
{

public:

	NormalParticleRigidGenerator(RigidParticle* rp_, int n, double _generation_probability_);
	~NormalParticleRigidGenerator() {};

	std::list<RigidParticle*> generateParticles() override;
	void setDistribution() override {};

};

