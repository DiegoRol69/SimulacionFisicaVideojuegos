#pragma once
#include "RigidParticle.h"

class Enemy:public RigidParticle
{
public:
	Enemy(PxRigidDynamic* solid_, double tiempoVida_, RenderItem* item_);
	~Enemy();

	void integrate(double t) override;

private:

	RenderItem* head;
	RenderItem* body;

};