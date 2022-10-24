#pragma once
#include "ParticleGenerator.h"
#include "FireWork.h"

class CircleParticleGen :public ParticleGenerator
{
	double radius;
	double angle = 90;

public:

	CircleParticleGen(Particle* p, int n, double _generation_probability_, double radius_);

	~CircleParticleGen() {};

	std::list<Particle*> generateParticles() override;
	void setPosCircle(double angle);
	void setDistribution() override{};
};

