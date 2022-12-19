#include "EnemiesSpawn.h"

EnemiesSpawn::EnemiesSpawn(PxShape* shape_, names name_, int n,
	double _generation_probability_, double dev_t_, double mean_t_)
{
	shape = shape_;
	name = name_;
	mean_t = mean_t_;
	dev_t = dev_t_;
	num_particles = n;
	_generation_probability = _generation_probability_;
}

std::list<RigidParticle*> EnemiesSpawn::generateParticles(PxPhysics* gPhysics)
{
	std::uniform_real_distribution<double> generationDistr(0, 1);
	std::uniform_real_distribution<double> density(1, 600);
	std::uniform_real_distribution<double> color(0, 1);

	std::list<RigidParticle*> particles;

	setDistribution();

	int x = mean_pos.x;

	for (int i = 0; i < num_particles; i++) {
		if (generationDistr(gen) < _generation_probability) {

			PxRigidDynamic* new_solid;

			mean_pos.x = x + (i * 10);

			new_solid = gPhysics->createRigidDynamic(PxTransform(mean_pos));
			new_solid->setLinearVelocity(mean_vel);
			new_solid->setAngularVelocity({ 0,0,0 });
			new_solid->attachShape(*shape);
			PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, density(gen));

			item = new RenderItem(shape, new_solid, { float(color(gen)), float(color(gen)), float(color(gen)), 1 });

			Enemy* rp = new Enemy(new_solid, 0, item);
			rp->setTypeName(name);

			particles.push_back(rp);
		}
	}

	return particles;
}

