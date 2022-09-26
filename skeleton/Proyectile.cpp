#include "Proyectile.h"
#include "RenderUtils.hpp"

using namespace physx;

Proyectile::Proyectile(TipoBala t):Particle()
{
	Camera* camera = GetCamera();
	Vector3 posCamera = camera->getTransform().p;

	switch (t)
	{
	case ARTILLERY:
		setProyectile(posCamera , 40 * camera->getDir(), 0.8, Vector3(0, -9.8, 0), 440, CreateShape(physx::PxSphereGeometry(10)));
		break;
		
	case PISTOL:
		setProyectile(posCamera, 80 * camera->getDir(), 0.99, Vector3(0, -9.8, 0), 5, CreateShape(physx::PxSphereGeometry(1)));
		break;

	case FIREBALL:
		setProyectile(posCamera, 20 * camera->getDir(), 0.7, Vector3(0, -1, 0), 100, CreateShape(physx::PxSphereGeometry(10)));
		break;

	default:
		break;
	}
}
