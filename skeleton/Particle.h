#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <random>

struct particleProperties {
	Vector3 vel;
	Vector3 aceleration;
	double damping;
	double masa;
	double tiempoVida;
	physx::PxShape* shape;	
	physx::PxTransform pose;
	RenderItem* renderItem;
};

class Particle
{
public:

	Particle() {};
	Particle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double tiempoVida_);
	~Particle();
	void setParticle(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, physx::PxShape* shape, double tiempoVida_, bool prefab);

	virtual Particle* clone();
	void copyParticle(Particle* p);

	particleProperties getProperties();

	void integrate(double t);
	bool viva();

	void setTime(double time);
	void setPos(Vector3 pos);
	void setVel(Vector3 vel);

protected:
	particleProperties properties;
	Vector3 space;
	std::random_device rd{};
	std::mt19937 gen{ rd() };
};

