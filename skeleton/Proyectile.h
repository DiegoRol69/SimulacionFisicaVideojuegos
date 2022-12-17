#pragma once
#include "RigidParticle.h"

enum TipoBala {PISTOL, ARTILLERY, FIREBALL};

class Proyectile : public RigidParticle
{
public:
	Proyectile(PxRigidDynamic* solid_, double tiempoVida, bool destroyable, RenderItem* item);
	~Proyectile();

	void onCollision(names mn, ParticleSys* pSys) override;
};

