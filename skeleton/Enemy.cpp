#include "Enemy.h"

Enemy::Enemy(PxRigidDynamic* solid_, double tiempoVida_, RenderItem* item_):RigidParticle(solid_, tiempoVida_, item_) {
	
	PxTransform p(solid_->getGlobalPose().p.x, solid_->getGlobalPose().p.y, solid_->getGlobalPose().p.z);

	head = new RenderItem(CreateShape(PxSphereGeometry(0.5)), solid_, &p, {1.0,0.0,0.0, 1.0});

	p.p.y = solid_->getGlobalPose().p.y - 50;

	body = new RenderItem(CreateShape(PxSphereGeometry(1.5)), solid_, &p, {1.0,0.0,0.0, 1.0});

}

void Enemy::integrate(double t) {
	RigidParticle::integrate(t);

}