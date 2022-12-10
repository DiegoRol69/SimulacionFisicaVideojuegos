#include "NormalParticleRigidGenerator.h"

NormalParticleRigidGenerator::NormalParticleRigidGenerator(RigidParticle* rp_, int n, double _generation_probability_)
{
	_model = rp_;
	num_particles = n;
	_generation_probability = _generation_probability_;
}

std::list<RigidParticle*> NormalParticleRigidGenerator::generateParticles()
{
    std::uniform_real_distribution<double> generationDistr(0, 1);

    std::list<RigidParticle*> particles;

    setDistribution();

    for (int i = 0; i < num_particles; i++) {
        if (generationDistr(gen) < _generation_probability && i < MAX_P) {

           /* Particle* p = _model->clone();
            particles.push_back(p);*/
        }
    }

    return particles;
}
