#pragma once
#include <list>
#include "Particle.h"
#include <random>

class ParticleGenerator
{

protected:

	Vector3 mean_pos, mean_vel, pos_result, vel_result;

	double _generation_probability, mean_t;

	int num_particles;

	Particle* _model;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

public:

	virtual std::list<Particle*> generateParticles () = 0;

	void setMeans(Vector3 mean_pos_, Vector3 mean_vel_) {
		mean_pos = mean_pos_;
		mean_vel = mean_vel_;
	}

};

