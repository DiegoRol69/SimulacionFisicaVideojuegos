#include "Enemy.h"

Enemy::Enemy(PxRigidDynamic* solid_, double tiempoVida_, RenderItem *item):RigidParticle(solid_, tiempoVida_, false, item) {
	
    ph = PxTransform(solid_->getGlobalPose().p.x, solid_->getGlobalPose().p.y + 6, solid_->getGlobalPose().p.z);

	head = new RenderItem(CreateShape(PxSphereGeometry(2)), solid_, &ph, {1.0,0.0,0.0, 1.0});

	pb = PxTransform(solid_->getGlobalPose().p.x, solid_->getGlobalPose().p.y, solid_->getGlobalPose().p.z);

	body = new RenderItem(CreateShape(PxSphereGeometry(5)), solid_, &pb, {1.0,0.0,0.0, 1.0});
}

void Enemy::integrate(double t) {
	RigidParticle::integrate(t);

	PxRigidDynamic* solid_ = getDynamicP();

	ph = PxTransform(solid_->getGlobalPose().p.x, solid_->getGlobalPose().p.y + 6, solid_->getGlobalPose().p.z);
	pb = PxTransform(solid_->getGlobalPose().p.x, solid_->getGlobalPose().p.y, solid_->getGlobalPose().p.z);
}

void Enemy::onCollision(names mn, ParticleSys* pSys) {

	setAlive(false);
}

Enemy::~Enemy() {
	DeregisterRenderItem(head);
	DeregisterRenderItem(body);
}