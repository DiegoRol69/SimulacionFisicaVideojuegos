#include "UniformParticleGen.h"

UniformParticleGen::UniformParticleGen(Vector3 pos, Vector3 vel, int n, double _generation_probability_, Vector3 pos_width_, Vector3 vel_width_)
{
    mean_pos = pos;
    mean_vel = vel;
    num_particles = n;
    _generation_probability = _generation_probability_;
    pos_width = pos_width_;
    vel_width = vel_width_;

    px = std::uniform_real_distribution<>(mean_pos.x-pos_width.x/2, mean_pos.x + pos_width.x/2);
    py = std::uniform_real_distribution<>(mean_pos.y - pos_width.y/2, mean_pos.y + pos_width.y/2);
    pz = std::uniform_real_distribution<>(mean_pos.z - pos_width.z/2, mean_pos.z + pos_width.z/2);

    vx = std::uniform_real_distribution<>(mean_vel.x - vel_width.x/2, mean_pos.x + vel_width.x/2);
    vy = std::uniform_real_distribution<>(mean_vel.y - vel_width.y/2, mean_pos.x + vel_width.y/2);
    vz = std::uniform_real_distribution<>(mean_vel.z - vel_width.z/2, mean_pos.x + vel_width.x/2);

}

std::list<Particle*> UniformParticleGen::generateParticles()
{
    std::uniform_real_distribution<double> generationDistr(0, 1);

    std::list<Particle*> particles;

    for (int i = 0; i < num_particles; i++) {
        if (generationDistr(gen) < _generation_probability) {

            pos_result = { float(px(gen)), float(py(gen)), float(pz(gen)) };
            vel_result = { float(vx(gen)), float(vy(gen)), float(vz(gen)) };

            Particle* p = new Particle(pos_result, vel_result, 0.99, Vector3(0, 10, 0), 3);

            particles.push_back(p);
        }
    }

    return particles;
}
