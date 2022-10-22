#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:

	Particle() {};
	Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double tiempoVida_);
	~Particle();
	void setParticle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, physx::PxShape* shape);

	virtual Particle* clone() const;

	Vector3 getPos();
	Vector3 getVel();

	void integrate(double t);
	bool viva();

	void setTime(double time);
	void setPos(Vector3 pos);

private:

	Vector3 vel;
	Vector3 aceleration;
	physx::PxTransform pose;
	RenderItem* renderItem;
	double damping;
	double masa;
	double tiempoVida;
	Vector3 space;
};

