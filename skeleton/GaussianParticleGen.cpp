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

    px = std::normal_distribution<> (mean_pos.x, dev_pos.x);
    py = std::normal_distribution<> (mean_pos.y, dev_pos.y);
    pz = std::normal_distribution<> (mean_pos.z, dev_pos.z);

    vx = std::normal_distribution<> (mean_vel.x, dev_vel.x);
    vy = std::normal_distribution<> (mean_vel.y, dev_vel.y);
    vz = std::normal_distribution<> (mean_vel.z, dev_vel.z);

}

std::list<Particle*> GaussianParticleGen::generateParticles()
{

    std::uniform_real_distribution<double> generationDistr(0, 1);
    std::normal_distribution<> t(mean_t, dev_t);

    std::list<Particle*> particles;

    for (int i = 0; i < num_particles; i++) {

        pos_result = { float(px(gen)), float(py(gen)), float(pz(gen)) };
        vel_result = { float(vx(gen)), float(vy(gen)), float(vz(gen)) };

        if (generationDistr(gen) < _generation_probability) {
            Particle* p = new Particle(pos_result, vel_result, 0.99, Vector3(0, -10, 0), t(gen));
            particles.push_back(p);
        }
    }

    return particles;
}
