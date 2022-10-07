#include "GaussianParticleGen.h"

GaussianParticleGen::GaussianParticleGen(Vector3 pos, Vector3 vel,  int n, Vector3 dev_pos_, 
    Vector3 dev_vel_, double _generation_probability_, double dev_t_, double mean_t_)
{
    mean_pos = pos;
    mean_vel = vel;
    num_particles = n;
    dev_pos = dev_pos_;
    dev_vel = dev_vel_;
    _generation_probability = _generation_probability_;
    dev_t = dev_t_;
    mean_t = mean_t_;
}

std::list<Particle*> GaussianParticleGen::generateParticles()
{

    std::normal_distribution<> px(mean_pos.x, dev_pos.x);
    std::normal_distribution<> py(mean_pos.y, dev_pos.y);
    std::normal_distribution<> pz(mean_pos.z, dev_pos.z);

    pos_result = { float(px(gen)), float(py(gen)), float(pz(gen)) };

    std::normal_distribution<> vx(mean_vel.x, dev_vel.x);
    std::normal_distribution<> vy(mean_vel.y, dev_vel.y);
    std::normal_distribution<> vz(mean_vel.z, dev_vel.z);

    vel_result = { float(vx(gen)), float(vy(gen)), float(vz(gen)) };

    std::uniform_real_distribution<double> generationDistr(0, 1);

    std::normal_distribution<> t(mean_t, dev_t);

    std::list<Particle*> particles;

    for (int i = 0; i < num_particles; i++) {
        if (generationDistr(gen) < _generation_probability) {
            Particle* p = new Particle(pos_result, vel_result, 0.99, Vector3(0, -9.8, 0), t(gen));
            particles.push_back(p);
        }
    }

    return particles;
}
