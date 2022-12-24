#include "Proyectile.h"
#include "RenderUtils.hpp"

using namespace physx;

Proyectile::Proyectile(PxRigidDynamic* solid_, double tiempoVida, bool destroyable, RenderItem* item):
	RigidParticle(solid_, tiempoVida, destroyable, item)
{
}

Proyectile::~Proyectile()
{
}

void Proyectile::onCollision(names mn, ParticleSys* pSys) {

	Vector3 pos = getDynamicP()->getGlobalPose().p;

	switch (getTypeName())
	{
	case BulletFW:
		pSys->generateFireworkInPos(pos, Gaussian, 15);
		break;
	case Bomb:
		pSys->generateFireworkInPos(pos, Circle, 20);
		break;
	default:
		break;
	}

	setAlive(false);
}
