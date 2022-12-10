#pragma once
#pragma once
#include "ParticleRigidGenerator.h"

class NormalParticleRigidGenerator :public ParticleRigidGenerator
{
	double dev_t;

public:

	NormalParticleRigidGenerator(PxShape* shape_, char* name_, int n, double _generation_probability_, 
		double dev_t_, double mean_t_);
	~NormalParticleRigidGenerator() {};

	std::list<RigidParticle*> generateParticles(PxPhysics *gPhysics) override;
	void setDistribution() override {};

};

