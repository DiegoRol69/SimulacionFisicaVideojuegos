#pragma once
#include <list>
#include "Particle.h"

class ParticleGenerator
{

protected:

	Vector3 mean_pos, mean_vel, pos_result, vel_result;

	double _generation_probability, mean_t;

	int num_particles;

	Particle* _model;

public:

	virtual std::list<Particle*> generateParticles () = 0;

};

