#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle() {};
	Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double tiempoVida_);
	~Particle();

	void integrate(double t);
	bool viva();

	virtual Particle* clone () const;

private:

	Vector3 vel;
	Vector3 aceleration;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping;
	double masa;
	double tiempoVida;
	Vector3 space;

protected:
	void setProyectile(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m,  physx::PxShape * shape);
};

