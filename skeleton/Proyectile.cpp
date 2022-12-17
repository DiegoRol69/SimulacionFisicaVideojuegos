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
	pSys->generateFireworkInPos(getDynamicP()->getGlobalPose().p);
	setAlive(false);
}
