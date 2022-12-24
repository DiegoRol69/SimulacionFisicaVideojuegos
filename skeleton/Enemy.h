#pragma once
#include "RigidParticle.h"

class Enemy:public RigidParticle
{
public:
	Enemy(PxRigidDynamic* solid_, double r_, double tiempoVida, RenderItem *item);
	~Enemy();

	void integrate(double t) override;
	void onCollision(names mn, ParticleSys* pSys) override;
	double getRadius();

private:

	RenderItem* head;
	RenderItem* body;
	PxTransform pb;
	PxTransform ph;

	double r;
	int lives = 3;
};