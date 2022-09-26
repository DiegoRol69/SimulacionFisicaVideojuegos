#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle() {};
	Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel);
	~Particle();

	void integrate(double t);

private:

	Vector3 vel;
	Vector3 aceleration;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping;
	double masa;

protected:
	void setProyectile(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m,  physx::PxShape * shape);
};

