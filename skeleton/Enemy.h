#pragma once
#include "RigidParticle.h"

class Enemy:public RigidParticle
{
public:
	Enemy(PxRigidDynamic* solid_, double tiempoVida, RenderItem *item);
	~Enemy();

	void integrate(double t) override;
	void onCollision(names mn, ParticleSys* pSys) override;

private:

	RenderItem* head;
	RenderItem* body;
	PxTransform pb;
	PxTransform ph;

};