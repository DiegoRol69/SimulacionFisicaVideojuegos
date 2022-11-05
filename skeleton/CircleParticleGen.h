#pragma once
#include "ParticleGenerator.h"
#include "FireWork.h"

enum typeC {FunteChocolate, FunteAgua, ult};

class CircleParticleGen :public ParticleGenerator
{
	double radius;
	double angle = 90;
	typeC tipoCircle;
	typeF tipoF;

public:

	CircleParticleGen(Particle* p, int n, double _generation_probability_, double radius_, 
		typeC tipo_, typeF tipoF_);

	~CircleParticleGen() {};

	std::list<Particle*> generateParticles() override;
	void setPosCircle(double angle);
	void setDistribution() override{};
	void setForceToClon() override;
	ForceGenerator *getTypeF() override;
};

