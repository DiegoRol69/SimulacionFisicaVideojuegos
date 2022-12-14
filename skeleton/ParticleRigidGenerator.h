#pragma once

#pragma once
#include <list>
#include <random>
#include "RigidParticle.h"

class ParticleRigidGenerator
{

protected:

	Vector3 mean_pos, mean_vel, pos_result, vel_result;
	PxShape* shape;
	RenderItem* item;
	
	double _generation_probability, mean_t, mass;
	int num_particles;
	char* name;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

public:

	virtual std::list<RigidParticle*> generateParticles(PxPhysics* gPhysics) = 0;
	virtual void setDistribution() = 0;

	void setMeans(Vector3 mean_pos_, Vector3 mean_vel_) {
		mean_pos = mean_pos_;
		mean_vel = mean_vel_;
	}

};


