#pragma once
#include "ParticleGenerator.h"
#include "FireWork.h"

enum type {FunteChocolate, FunteAgua, ult};

class CircleParticleGen :public ParticleGenerator
{
	double radius;
	double angle = 90;
	type tipo;

public:

	CircleParticleGen(Particle* p, int n, double _generation_probability_, double radius_, type tipo_);

	~CircleParticleGen() {};

	std::list<Particle*> generateParticles() override;
	void setPosCircle(double angle);
	void setDistribution() override{};
};

