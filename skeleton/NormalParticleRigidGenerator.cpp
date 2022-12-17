#include "NormalParticleRigidGenerator.h"

NormalParticleRigidGenerator::NormalParticleRigidGenerator(PxShape* shape_, char *name_, int n, 
	double _generation_probability_, double dev_t_, double mean_t_)
{
	shape = shape_;
	name = name_;
	mean_t = mean_t_;
	dev_t = dev_t_;
	num_particles = n;
	_generation_probability = _generation_probability_;
}

std::list<RigidParticle*> NormalParticleRigidGenerator::generateParticles(PxPhysics* gPhysics)
{
    std::uniform_real_distribution<double> generationDistr(0, 1);
    std::uniform_real_distribution<double> density(1, 600);
	std::uniform_real_distribution<double> color(0, 1);
	std::normal_distribution<> t(mean_t, dev_t);

    std::list<RigidParticle*> particles;

    setDistribution();

    for (int i = 0; i < num_particles; i++) {
        if (generationDistr(gen) < _generation_probability) {

			PxRigidDynamic* new_solid;

			new_solid = gPhysics->createRigidDynamic(PxTransform(mean_pos));
			new_solid->setLinearVelocity(mean_vel);
			new_solid->setAngularVelocity({ 0,0,0 });
			new_solid->attachShape(*shape);
			PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, density(gen));

			item = new RenderItem(shape, new_solid, { float(color(gen)), float(color(gen)), float(color(gen)), 1 });
			new_solid->setName(name);

			Enemy * rp = new Enemy(new_solid, t(gen), item);

			particles.push_back(rp);
        }
    }

    return particles;
}
