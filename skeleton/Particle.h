#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, double damp, Vector3 acel);
	~Particle();

	void integrate(double t);

private:

	Vector3 vel;
	Vector3 aceleration;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping;
};

