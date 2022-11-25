#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchorPos):SpringForceGenerator(k, resting, nullptr)
{

	other = new Particle();

	other->setParticle(anchorPos, {0,0,0}, 0, {0,0,0}, 1e6,
		CreateShape(physx::PxBoxGeometry(1,1,1)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, 0);

}
